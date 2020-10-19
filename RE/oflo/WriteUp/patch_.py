from idaapi import *
def PatchXor(addr, length):
    x = "n1ctf"
    for i in range(length):
        nowByte = idc.Byte(addr + i)
        xorByte = (nowByte ^ ord(x[i%5]))
        idc.PatchByte(addr + i, xorByte);
    print 'Patch finished'

PatchXor(0x0400A69, 10)