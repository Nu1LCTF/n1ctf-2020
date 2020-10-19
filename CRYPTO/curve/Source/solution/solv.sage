#!/usr/bin/env sage

import subprocess, string, hashlib, os, itertools
os.environ["TERM"] = 'screen'

NBITS = 521
NROUNDS = 30

# https://journals.plos.org/plosone/article?id=10.1371/journal.pone.0161857
def find_r(numbits):
  while True:
    s = randrange(0, numbits - 1)
    t = randrange(s + 1, numbits)
    r = 1 + 2^s + 2^t + 2^(numbits-1)
    if not is_prime(r):
      continue 
    return r

def find_pu(numbits):
  while True:
    r = find_r(numbits // 2)
    u = r * r
    p = u + r + 1
    if is_prime(p):
      return p, u, r

def find_curve(numbits):
  p, u, r = find_pu(numbits)
  E = EllipticCurve(GF(p), j=0)
  orig = E
  if E.order() == u:
    return E
  E = E.quadratic_twist()
  if E.order() == u:
    return E
  i = 1
  while E.order() != u and i < 10000:
    E = orig.sextic_twist(i)
    i += 1
  return p, u, r, E

p, u, r, E = find_curve(NBITS)
a = E.a_invariants()[3]
b = E.a_invariants()[4]
print(E)

assert p.nbits() > 512

from pwn import *

#io = process(["sage", "../chall.sage"])
io = remote('47.242.140.57', 9998)

io.recvuntil("sha256(")
prefix = io.recvuntil("+", drop=True).decode()
io.recvuntil(" == ")
h = io.recvline().decode().strip()

for comb in itertools.product(string.ascii_letters + string.digits, repeat=4):
  s = prefix + "".join(comb)
  if hashlib.sha256(s.encode()).hexdigest() == h:
    io.sendlineafter("XXXX: ", "".join(comb))
    break

io.sendlineafter("P: ", str(p))
io.sendlineafter("A: ", str(a))
io.sendlineafter("B: ", str(b))

def read_point():
  io.recvuntil("(")
  x = ZZ(io.recvuntil(":", drop=True).decode().strip())
  y = ZZ(io.recvuntil(":", drop=True).decode().strip())
  return E((x, y))

G1, G2 = E.gens()
io.sendlineafter("X1: ", str(G1[0]))
io.sendlineafter("Y1: ", str(G1[1]))
io.sendlineafter("X2: ", str(G2[0]))
io.sendlineafter("Y2: ", str(G2[1]))

for _ in range(NROUNDS):
  g1 = read_point()
  g2 = read_point()
  c = read_point()
  if g2.weil_pairing(g1, r) == G2.weil_pairing(c, r):
    io.sendlineafter("Choice: ", "0")
  else:
    io.sendlineafter("Choice: ", "1")

io.interactive()

