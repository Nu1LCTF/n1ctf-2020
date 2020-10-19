#!/usr/bin/env python2
# -*- coding:utf-8 -*-

import string, random, os, re, sys, json, SocketServer, subprocess, uuid, hashlib, logging, base64

CONFIG_PATH = "C:\\challenge\\config.json"
CONFIG = json.loads(open(CONFIG_PATH, 'rb').read())

####################################################################
# Server code
####################################################################

def randstr(length=8):
  return ''.join([random.choice(string.ascii_letters + string.digits) for i in xrange(length)])

def valid(name):
  if len(name) > 40 or len(name) == 0:
    return False
  if not all(ord(c) < 128 for c in name):
    return False
  if re.match("[a-zA-Z0-9]*", name).group() != name:
    return False
  return True

class TRTCPServer(SocketServer.ThreadingMixIn, SocketServer.ThreadingTCPServer):
  pass    

class TRTCPHandler(SocketServer.StreamRequestHandler):
  def read_exact(self, nbytes):
    result = ''
    rem = nbytes 
    while rem:
      result += self.rfile.read(rem)
      rem = nbytes - len(result)
    return result 

  def banner(self):
    req = self.request
    req.sendall("Welcome to this service!\n")
    req.sendall("Default timeout is %d seconds, and will be activated after receiving your PoW.\n" % CONFIG["timeout"])
    req.sendall("After validating your PoW, the server will execute your PE binary.\n")
    req.sendall("Your binary should not exceed the size limit of %d bytes.\n" % CONFIG["size_limit"])
    req.sendall("Try to get the flag at C:\\flag.txt!\n")
    req.sendall("Since this is an experimental task, ask admins if you got into any trouble.\n")
    return True

  def proof_of_work(self):
    req = self.request
    s = randstr(20)
    h = hashlib.sha256(s).hexdigest()
    p = s[:16]
    req.sendall("sha256(%s+XXXX) == %s\n" % (p, h))
    req.sendall("Give me XXXX: ")
    try:
      suf = self.rfile.readline().strip()
    except Exception:
      req.sendall("I/O error\n")
      req.close()
      return False

    if len(suf) == 4 and hashlib.sha256(p + suf).hexdigest() == h:
      return True 
    return False
  
  def handle(self):
    req = self.request

    self.banner()
    req.sendall("Give me your name (your ID or your team ID)\n")
    req.sendall("Alphabet chars and digits only, no longer than 40 chars: ")
    try:
      teamname = self.rfile.readline().strip()
    except Exception:
      req.sendall("I/O error\n")
      req.close()
      return

    if not valid(teamname):
      req.sendall("Invalid name.\n")
      req.sendall("Please use alphabet characters and digits only.\n")
      req.sendall("Make sure your string won't exceed the length limit.\n")
      req.close()
      return

    if not self.proof_of_work():
      req.sendall("Invalid PoW.\n")
      req.close()
      return

    req.settimeout(CONFIG["timeout"])
    req.sendall("The byte size of you executable: ")
    try:
      pe_size = long(self.rfile.readline().strip())
    except Exception:
      req.sendall("Invalid input.")
      req.close()
      return

    if pe_size >= CONFIG["size_limit"]:
      req.sendall("No you don't need such a huge executable.\n")
      req.sendall("Try to reduce the size of your solution.\n")
      req.close()
      return

    if pe_size <= 10:
      req.sendall("No kidding, this is a serious challenge. :)\n")
      req.close()
      return
    
    req.sendall("Got it, send me exactly %d bytes: " % pe_size)
    try:
      binary = self.read_exact(pe_size)
    except:
      req.sendall("Error when receiving binary.\n")
      req.close()
      return
    
    if not binary.startswith('MZ'):
      req.sendall("Not a valid PE file.\n")
      req.sendall("Try send me some valid executables.\n")
      req.close()
      return

    filename = teamname + '-' + randstr() + '.exe'
    filepath = CONFIG["solution_dir"] + filename
    cappath = CONFIG["capture_dir"] + filename
    try:
      open(filepath, 'wb').write(binary)
      open(cappath, 'wb').write(binary)
    except Exception, ex:
      req.sendall("Error saving solution, contact admin.\n")
      req.sendall("Exception: " + str(ex) + "\n")
      req.close()
      return

    req.sendall("Got it, running your solution...\n")
    pipe_name = str(uuid.uuid4())
    chal_proc = subprocess.Popen([CONFIG["chal_bin"], pipe_name])
    try:
      output = subprocess.check_output([CONFIG["sandbox"], CONFIG["sandbox_profile"], filepath, pipe_name])
    except Exception, ex:
      logger.info("Solution exception: %s" % str(ex))
      req.sendall("Error when executing your binary, please check.\n")
      req.sendall("Exception: " + str(ex) + "\n")
      os.remove(filepath)
      req.close()
      return

    self.wfile.write("Output:\n")
    self.wfile.write(output)
    #req.close()

    # cleanup
    chal_proc.terminate()
    os.remove(filepath)
    return


####################################################################
# Svc code
####################################################################

if __name__ == '__main__':
  os.chdir(CONFIG["work_dir"])
  server = TRTCPServer(('0.0.0.0', 13337), TRTCPHandler)
  server.allow_reuse_address = True
  server.serve_forever()
