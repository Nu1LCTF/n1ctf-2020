import random
import sys
from hashlib import sha256
from string import ascii_letters, digits


flag = b"n1ctf{S0me_kn0wl3dg3_is_leak3d}"


def proof_of_work():
    proof = ''.join([random.choice(ascii_letters+digits) for _ in range(20)])
    _hexdigest = sha256(proof.encode()).hexdigest()
    print(f"character set: {ascii_letters+digits}")
    print(f"sha256(XXXX+{proof[4:]}) == {_hexdigest}")
    print("Give me XXXX: ", end="")
    try:
        prefix = sys.stdin.read(4)
    except:
        exit(1)
    return sha256((prefix+proof[4:]).encode()).hexdigest() == _hexdigest