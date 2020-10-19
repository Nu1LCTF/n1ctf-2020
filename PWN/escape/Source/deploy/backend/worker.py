#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, logging, subprocess, signal, time, tempfile, json, shutil
import sqlite3, shlex, pipes, beanstalkc, docker, requests, string, random, pika

### general configuration
DATABASE = '/shared/tickets.sqlite3'
WORKER_ID = int(sys.argv[1]) if len(sys.argv) >= 2 else 0
LOG_FILE = '/challenge/log/worker-%d.log' % (WORKER_ID)
COLLECT_DIR = '/challenge/attempts/'
URL_FETCH_TIMEOUT = 10

### docker related configuration
DOCKER_IMAGE = "pwnable"
CONTAINER_TIMEOUT = 60

### globals
logging.basicConfig(level=logging.INFO, filename=LOG_FILE, filemode='a', format='[%(asctime)s] %(levelname)s - %(message)s', stream=sys.stdout)
logger = logging.getLogger("chal.worker")
DEVNULL = open(os.devnull, "wb")

### docker client
client = docker.from_env()

### utils
randstr = lambda x: ''.join([random.choice(string.ascii_letters) for _ in xrange(x)])

### low quality docker automation
class RunDocker(object):
  def __init__(self):
    self._container = None 
    return

  # retrieve player's exploit
  def retrieve_url(self, url):
    out_dir = COLLECT_DIR + "/" + "_".join([time.strftime("%Y-%m-%d-%H-%M-%S"), randstr(8)])
    
    logger.debug("Retrieving url (%s) to word directory (%s)...", url, out_dir)
    proc = subprocess.Popen(
      ["/usr/bin/timeout", str(URL_FETCH_TIMEOUT), "wget", "-p", "-k", "-P", out_dir, url],
      stdin=DEVNULL,
      stdout=DEVNULL,
      stderr=DEVNULL
      ) 

    retcode = proc.wait()
    if retcode != 0:
      return False
    return True 

  def _run_url(self, url):
    # create the container
    logger.debug("Creating container...")
    self._container = client.containers.create(DOCKER_IMAGE, [
      "chromium-browser", 
      "--headless", 
      "--disable-gpu", 
      "--no-sandbox",
      "--js-flags=--noexpose_wasm",
      "--virtual-time-budget=60000",
      url 
    ])

    # start the container & wait for it
    logger.debug("Starting container...")
    self._container.start()

    logger.debug("Waiting container...")
    try:
      exitcode = self._container.wait(timeout=CONTAINER_TIMEOUT)
    except requests.exceptions.ReadTimeout:
      logger.debug("Container timed out.")
      self._container.kill(signal.SIGKILL)
    except Exception, ex:
      logger.warn("Some weird error... %s", str(ex))
      self._container.kill(signal.SIGKILL)  # kill it anyway

    logger.debug("Removing container...")
    self._container.remove()
    
    logger.info("Job completed")
    return 1

  def run_url(self, url):
    if not self.retrieve_url(url):
      return 3
    return self._run_url(url)

### sqlite integration
def resolve_ticket(ticket, status):
  try:
    conn = sqlite3.connect(DATABASE)
    conn.execute('UPDATE submissions SET status = ? WHERE ticket = ?', (status, ticket, ))
    conn.commit()
    conn.close()
  except Exception, ex:
    logger.warn("Exception when updating database: %s", str(ex))
    return False
  return True

### test
def test():
  runner = RunDocker()
  runner._run_url("http://httpbin.org/")
  return

### main
def main():
  connection = pika.BlockingConnection(pika.ConnectionParameters(host='localhost'))
  channel = connection.channel()
  channel.queue_declare('submission')

  logger.info("Starting backend worker %d, connected to docker & beanstalkd.", WORKER_ID)
  def on_message(ch, method, properties, body):
    try:
      data = json.loads(body)

      ticket = data['ticket']
      url = data['url']
      logger.info("Received challenge submission: %s (%s).", ticket, url)

      runner = RunDocker()
      status = runner.run_url(url)
      result = resolve_ticket(ticket, status)

      if not result:
        logger.warn("Update database failed, resolve this problem IMMEDIATELY!")
    except Exception, ex:
      logger.warning("Exception when processing: %s", str(ex))
    return

  channel.basic_consume('submission', on_message, auto_ack=True)
  logger.debug("Start consuming submission messages...")
  channel.start_consuming()

  # this never ends
  return 1

if __name__ == '__main__':
  sys.exit(main())

