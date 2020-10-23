import random

# Check crcollider.py at: https://github.com/yype/crcollider
from crcollider import collcrc

from crc_funcs import crc64, crc32

def crc96(m):
    return (crc32(m) << 64) + crc64(m)

def solve_chal():
    with open('credential.png', 'rb') as f:
        org_img = f.read()

    rg = list(range(len(org_img)*8))
    available_bits = []
    for i in range(12):
        # even bytes in the last 25 bytes
        available_bits += rg[len(rg)-16*i-16:len(rg)-16*i-8]

    sol_num, sols = collcrc(crc96, 96, org_img, available_bits, 0x0)
    
    print(f'{sol_num} solution(s) found')

    for i, each in enumerate(sols):
        file_out = f'credential_sol{i}.png'
        print(f'Outputting sol{i} to {file_out}...')
        with open(file_out, 'wb') as f:
            f.write(each)

if __name__ == '__main__':
    solve_chal()
