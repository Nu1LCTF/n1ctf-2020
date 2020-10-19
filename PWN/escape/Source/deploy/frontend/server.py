#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, hashlib, string, random, time, json, sqlite3, struct, beanstalkc, pika
from flask import Flask, redirect, render_template, session, request, url_for, send_from_directory, g

app = Flask(__name__)
app.secret_key = 'c3c5f97b668ab758e4b0ff7af4361124'

# challenge settings
DIFFICULTY = 26
URL_WHITELIST = string.ascii_letters + string.digits + '/:.%@'
DATABASE_PATH = '/shared/tickets.sqlite3'
BEANSTALK_HOST = 'localhost'
CHALLENGE_ID = 1
TIME_TO_RUN = 360

randstr = lambda x: ''.join([random.choice(string.ascii_letters) for _ in xrange(x)])

def generate_ticket():
  salt = randstr(12)
  s = salt + str(time.time())
  return hashlib.sha256(s).hexdigest()

def check_pow(chal, suffix):
  work = chal + struct.pack("<Q", suffix)
  bits = '{0:0256b}'.format(int(hashlib.sha256(work).hexdigest(), 16))
  if not bits.endswith(DIFFICULTY * '0'):
    return False
  return True

def check_url(url):
  if not url.startswith("http://") and not url.startswith("https://"):
    return False
  if not all([u in URL_WHITELIST for u in url]):
    return False
  return True

def get_db():
  db = getattr(g, '_database', None)
  if db is None:
    db = g._database = sqlite3.connect(DATABASE_PATH)
  return db

def get_beanstalk():
  conn = getattr(g, '_beanstalk', None)
  if conn is None:
    conn = g._beanstalk = beanstalkc.Connection(host=BEANSTALK_HOST)
  return conn

'''
CREATE TABLE submissions (ticket VARCHAR(255) NOT NULL UNIQUE, status INT NOT NULL)
'''
def put_sql(ticket):
  try:
    cur = get_db().cursor()
    cur.execute('INSERT INTO submissions VALUES (?, ?)', (ticket, 0, ))
    get_db().commit()
  except Exception, ex:
    print str(ex)
    return False
  return True

def get_sql(ticket):
  try:
    cur = get_db().cursor()
    res = cur.execute('SELECT * FROM submissions WHERE ticket=?', (ticket, ))
    rows = res.fetchall()
    if len(rows) != 1:
      return -1
    row = rows[0]
    return row[1]
  except Exception, ex:
    return -1
  raise Exception("Unreachable")

def put_mq(url, ticket):
  try:
    conn = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
    chan = conn.channel()
    chan.queue_declare('submission')

    msg = json.dumps({'url': url, 'ticket': ticket, 'id': CHALLENGE_ID})
    chan.basic_publish(exchange='', routing_key='submission', body=msg)
    conn.close()
  except Exception, ex:
    print str(ex)
    return False
  return True

def put_submission(url, ticket):
  # put submission into MQ & SQL
  if not put_mq(url, ticket):
    return False
  if not put_sql(ticket):
    return False
  return True

## routes
@app.route('/js/<path:filename>')  # will be replace by nginx static route
def javascript(filename):
  return send_from_directory('js', filename)

@app.route('/static/<path:filename>')
def staticfiles(filename):
  return send_from_directory('static', filename)

@app.route('/')
def index():
  PoW = randstr(8)
  session['PoW'] = PoW
  return render_template('index.html', chal=PoW, diff=DIFFICULTY, whitelist=URL_WHITELIST)

@app.route('/result/<ticket>')
def result(ticket):
  status = get_sql(ticket)
  return render_template('result.html', status=status)

@app.route('/submit', methods=['POST'])
def submit():
  if 'PoW' not in session:
    return json.dumps({'error': 1})
  
  chal = session['PoW']
  if not request.form.has_key('pow') or not request.form['pow'].isdigit():
    return json.dumps({'error': 2})
  suffix = int(request.form['pow'])

  if not check_pow(chal, suffix):
    return json.dumps({'error': 3})

  url = request.form['url']
  if not check_url(url):
    return json.dumps({'error': 4})
  ticket = generate_ticket()

  if not put_submission(url, ticket):
    return json.dumps({'error': 5})
  
  del session['PoW']
  return json.dumps({'error': 0, 'ticket': ticket})

@app.teardown_appcontext
def close_dbconn(ex):
  db = getattr(g, '_database', None)
  if db is not None:
    db.close()
  conn = getattr(g, '_beanstalk', None)
  if conn is not None:
    conn.close()
  return

if __name__ == '__main__':
  app.debug = False
  app.run(host="0.0.0.0", port=5000)

