from typing import List, Tuple
from itertools import product

def bit_array_to_bytes(a: List[int]) -> bytes:
    n = len(a)
    assert n % 8 == 0
    num = int("".join(map(str, a)), 2)
    num_hex = hex(num)[2:].rjust(n // 4, "0")
    return bytes.fromhex(num_hex)

def bytes_to_bit_array(a: bytes) -> List[int]:
    n = int(a.hex(), 16)
    bits = [int(b) for b in bin(n)[2:].rjust(len(a)*8, '0')]
    return bits

def num_to_bit_array(n: int, sz) -> List[int]:
    bits = [int(b) for b in bin(n)[2:].rjust(sz, '0')]
    return bits


def collcrc(crc_func, sz: int, msg: bytes, ctr_bits: List[int], target_crc: int) -> Tuple[int, List[bytes]]:
    """
    Return value: (number_of_solutions, [solutions])\n
    Arguments:\n
    crc_func: the CRC function to be used\n
    sz: the bit size of the target CRC value\n
    msg: the message to perform CRC on\n
    ctr_bits: controllable bits in the message, e.g. [0,1,2,3,4,5,6,7] for the first byte\n
    target_crc: the target CRC value\n
    """
    
    if len(ctr_bits) > sz:
        print(f'Please make sure len(ctr_bits) <= sz to avoid too many solutions, currently len(ctr_bits)={len(ctr_bits)} > sz={sz}')
        # Actually, I don’t want to write codes to support the case that len(ctr_bits)>sz :D
        exit(0)
        
    if target_crc // (1 << sz) != 0:
        print('Please recheck your target CRC value')
        exit(0)

    def get_bit1(num, j): return (num >> (sz-1-j)) & 1
    def get_bit2(num, j): return (num >> (len(ctr_bits)-1-j)) & 1

    bits = bytes_to_bit_array(msg)
    for each in ctr_bits:
        bits[each] = 0  # zero all ctr_bits
    zero_crc = crc_func(bit_array_to_bytes(bits))
    diffs = []
    for each in ctr_bits:
        _bits = bits[:]
        _bits[each] = 1  # alter
        _crc = crc_func(bit_array_to_bytes(_bits))
        diff = _crc ^ zero_crc
        diffs.append(diff)

    # diffs -> mat
    mat = [0] * sz
    for i in range(len(ctr_bits)):
        for j in range(sz):
            j_bit = get_bit1(diffs[i], j)
            mat[j] ^= j_bit << (len(ctr_bits)-i-1)

    b = num_to_bit_array(target_crc ^ zero_crc, sz)

    _mat, _b = mat[:], b[:]

    # solve mat * x = b (left inverse)
    for i in range(len(ctr_bits)):
        for j in range(i, len(mat)):
            if get_bit2(mat[j], i) == 1:
                mat[i], mat[j] = mat[j], mat[i]
                b[i], b[j] = b[j], b[i]
                break
        if get_bit2(mat[i], i) != 1:
            continue
        for j in range(len(mat)):
            if j != i and get_bit2(mat[j], i) == 1:
                mat[j] ^= mat[i]
                b[j] ^= b[i]

    '''
    # for debugging purposes
    for i, each in enumerate(mat):
        print(f'{i:02d}', bin(each)[2:].rjust(len(ctr_bits), '0'))
    '''

    free_x = 0
    free_x_idx = []
    non_free_x_idx = []
    for i in range(len(ctr_bits)-1,-1,-1):
        if mat[i] == 0:
            free_x_idx.append(len(ctr_bits)-1-i)
            free_x += 1
        else:
            non_free_x_idx.append(i)

    
    x = int(''.join(map(str, b)), 2) >> (sz-len(ctr_bits))

    try:
        for i in range(len(_mat)):
            tmp = x & _mat[i]
            pari = bin(tmp).count("1") % 2
            assert pari == _b[i]
    except AssertionError:
        # has no solution
        return (0, [])
        
    
    if free_x:
        # has multiple solutions
        results = []
        for each in product([0,1], repeat=free_x):
            _bits = bits[:]
            for i in non_free_x_idx:
                _bits[ctr_bits[i]] = b[i]
                for j, free_x_val in enumerate(each):
                    _bits[ctr_bits[i]] ^= ((mat[i]>>free_x_idx[j]) & 1) * free_x_val
            for i, idx in enumerate(free_x_idx):
                _bits[ctr_bits[-1-idx]] = each[i]
            
            result = bit_array_to_bytes(_bits)
            assert crc_func(result) == target_crc
            results.append(result)
        return (2**free_x, results)
    else:
        # has a single solution
        for i, each in enumerate(ctr_bits):
            bits[each] = b[i]
        result = bit_array_to_bytes(bits)
        assert crc_func(result) == target_crc
        return (1, [result])
