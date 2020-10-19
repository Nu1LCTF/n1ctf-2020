from Crypto.Util.Padding import pad, unpad
from Crypto.Util.number import long_to_bytes, bytes_to_long
from Crypto.Cipher import AES
from hashlib import sha256
import base64
import re

with open('output.txt', 'r') as f:
    lines = f.readlines()

N = 7

curves = [None for _ in range(N)]
g = [None for _ in range(N)]
S_pub = [None for _ in range(N)]
R_pub = [None for _ in range(N)]
encrypted_msg = [None for _ in range(N)]

for i in range(N):
    a, b, p = re.findall(r'\d{2,}', lines[i*4+0])
    a = int(a)
    b = int(b)
    p = int(p)
    E = EllipticCurve(GF(p), [a, b])
    curves[i] = E
    exec(lines[i*4+1])
    exec(lines[i*4+2])
    exec(lines[i*4+3])
    g[i] = E(g[i])
    S_pub[i] = E(S_pub[i])
    R_pub[i] = E(R_pub[i])

moduli = []
residues = []
for idx, curve in enumerate(curves):
    n = curve.order()
    fac = list(factor(n))
    for i, j in fac:
        modules = i**j
        if i > 1 << 40:
            break
        _g_ = g[idx]*ZZ(n/modules)
        _q_ = S_pub[idx]*ZZ(n/modules)
        residue = discrete_log(_q_, _g_, operation="+")
        moduli.append(modules)
        residues.append(residue)
        print(residue, modules)

secret = crt(residues, moduli)
encrypted_msg = [None]
exec(lines[4*N])
px = (R_pub[0]*secret).xy()[0]
_hash = sha256(long_to_bytes(px)).digest()
key = _hash[:16]
iv = _hash[16:]
msg = AES.new(key, AES.MODE_CBC, iv).decrypt(base64.b64decode(encrypted_msg[0]))
msg = unpad(msg, 16)
print(msg)
