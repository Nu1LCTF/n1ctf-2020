#!/usr/bin/env sage

import signal, hashlib, string, random, os 

os.chdir(os.path.dirname(os.path.abspath(__file__)))
FLAG = open("./flag.txt", 'r').read()
ROUNDS = 30

def PoW():
  s = ''.join([random.choice(string.ascii_letters + string.digits) for _ in range(20)])
  h = hashlib.sha256(s.encode()).hexdigest()
  prefix = s[:16]
  print("sha256(%s+XXXX) == %s" % (prefix, h))
  c = input("Give me XXXX: ")
  if hashlib.sha256((prefix + c).encode()).hexdigest() == h:
    return True 
  return False

def chall():
  p = ZZ(input("P: "))  # of course we are using sage >= 9
  a = ZZ(input("A: "))
  b = ZZ(input("B: "))

  if not is_prime(p) or p.nbits() < 512:
    print("No bad parameters.")
    return

  E = EllipticCurve(GF(p), [a, b])
  if E.is_supersingular():
    print("No this is not good enough.")
    return

  q = E.order()
  x1 = ZZ(input("X1: "))
  y1 = ZZ(input("Y1: "))
  x2 = ZZ(input("X2: "))
  y2 = ZZ(input("Y2: "))
  G1 = E((x1, y1))
  G2 = E((x2, y2))

  for _ in range(ROUNDS):
    a0 = randint(1, q - 1)
    a1 = randint(1, q - 1)

    c = -1
    while c == -1 or c == a0 * a1:
      c = randint(1, q - 1)

    g0, g1 = G1 * a0, G2 * a1 
    c0, c1 = G1 * (a0 * a1), G1 * c
    b = randint(0, 1)

    if b == 0:
      print(g0, g1, c0)
    else:
      print(g0, g1, c1)

    choice = ZZ(input("Choice: "))
    if choice != b:
      print("Wrong choice.")
      return

  print(f"Thank you! Here's your reward: {FLAG}")
  return 

if __name__ == '__main__':
  if not PoW():
    print("Invalid PoW.")
    exit()
  signal.alarm(90)

  try:
    chall()
  except:
    print("oof...")
    exit()

