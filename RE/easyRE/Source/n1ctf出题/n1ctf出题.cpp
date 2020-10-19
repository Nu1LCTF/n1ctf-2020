#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <excpt.h>
#include <iostream>
#include <Windows.h>
#include <bitset>
#include <conio.h>
#include <errhandlingapi.h>
using namespace std;

#define __mov 0x1000000
#define __add 0x2000000
#define __sub 0x3000000
#define __shl 0x4000000
#define __shr 0x5000000
#define __movzx 0x6000000
#define __or 0x7000000
#define __xor 0x8000000
#define __cmp 0x9000000
#define __retn 0xa000000
#define swap_handle 0xb000000
#define __jz 0xc000000

struct C_SCOPE_TABLE 
{
    unsigned int Begin;
    unsigned int End;
    unsigned int Handler;//__except filter
    unsigned int Target;//异常处理器
};

C_SCOPE_TABLE* base_of_scope_table = (C_SCOPE_TABLE*)0x40004A00;//

#define get_type_from() (cpu.eip->code&0xfff000)
#define get_type_to() (cpu.eip->code&0xfff)

struct opcode_struct
{
    unsigned int code;
    unsigned int arg1;
    unsigned int arg2;
};

struct cpu_
{
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int edi;
    unsigned int esi;
    opcode_struct* eip;
    unsigned int* ebp;
    unsigned int r7;
    unsigned int r8;
    unsigned int r9;
    unsigned int flag;
}cpu;

#define eax_from (0x100 << 12)
#define al_from (0x101 << 12)
#define ebx_from (0x200 << 12)
#define ecx_from (0x300 << 12)
#define edx_from (0x400 << 12)
#define dl_from (0x401 << 12)
#define edi_from (0x500 << 12)
#define esi_from (0x600 << 12)
#define memery_from (0x700 << 12)
#define imm_val_from (0x800 << 12)
#define base_of_ebp_from (0x900 << 12)
#define type_lea (0xa00 << 12)

#define eax_to (0x100)
#define al_to (0x101)
#define ebx_to (0x200)
#define ecx_to (0x300)
#define edx_to (0x400)
#define dl_to (0x401)
#define edi_to (0x500)
#define esi_to (0x600)
#define memery_to (0x700)
#define imm_val_to (0x800)
#define base_of_ebp_to (0x900)

/*
from:
rax 0x100 << 12
eax 0x110 << 12
 al 0x101 << 12
rbx 0x200 << 12
rcx 0x300 << 12
rdx 0x400 << 12
edx 0x410 << 12
 dl 0x401 << 12
rdi 0x500 << 12
rsi 0x600 << 12
memery 0x700 << 12
imm_val 0x800 << 12
rbp_mem 0x900 << 12



to:
rax 0x100
al 0x101
rbx 0x200
rcx 0x300
rdx 0x400
edx 0x410
 dl 0x401
rdi 0x500
rsi 0x600
memery 0x700
imm_val 0x800
rbp_mem 0x900

*/

/*
mov [ebp-xx],imm_val
mov reg(eax,edx),[ebp-xx]
mov [rbp-xx],reg(al)
mov [reg(edx,eax)],reg(al,dl)
mov reg(ecx,eax),reg(edx)

movzx eax,byte ptr [eax+xx]
movzx reg(edx,eax),reg(dl,al)
movzx reg(edx),byte ptr [edx]

lea edx,[eax+xx]        //mov edx,(eax+xx)

xor al,[rbp-xx]

add reg(eax,edx),imm_val
add reg(edx,eax),reg(eax,edx)

or edx, ecx

shr dl, 4

shl edx, 4

cmp eax, imm_val

sub edx, eax

jz 

retn

 */

unsigned char flag[100];

void tea_encrypt(uint32_t* v, uint32_t* k) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0, i;           /* set up */
    uint32_t delta = 1526574857;                     /* a key schedule constant */
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   /* cache key */
    for (i = 0; i < 123123; i++) {                       /* basic cycle start */
        sum *= delta;
        v0 += ((v1 << 3124) + k0) & (v1 + sum) ^ ((v1 >> 315) + k1);
        v1 += ((v0 << 3124) + k2) ^ (v0 + sum) ^ ((v0 >> 35) + k3);
    }                                              /* end cycle */
}
void tea_decrypt(uint32_t* v, uint32_t* k) {
    uint32_t v0 = v[0], v1 = v[1], sum = 2560173475, i;  /* set up */
    uint32_t delta = 2481885500;                     /* a key schedule constant */
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   /* cache key */
    for (i = 0; i < 3332; i++) {                         /* basic cycle start */
        v1 -= ((v0 << 1234) + k2) ^ (v0 + sum) ^ ((v0 >> 2135) + k3);
        v0 -= ((v1 << 3124) + k0) ^ (v1 + sum) ^ ((v1 >> 3125) + k1);
        sum -= delta;
    }                                              /* end cycle */
}
void xxtea(uint32_t* v, int n, uint32_t const key[4])
{
    uint32_t y, z, sum;
    unsigned p, rounds, e;
    if (n > 1)            /* Coding Part */
    {
        rounds = 116 + 512 / n;
        sum = 0;
        z = v[n - 1];
        do
        {
            sum += 3258949603;
            e = (sum >> 12) & 33;
            
            y = v[0];
            p = 0;
            z = v[n - 1] += (((z >> 15 ^ y << 212) + (y >> 33 ^ z << 234)) ^ ((sum ^ y) + (key[(p & 13) ^ e] ^ z)));
            for (p = 0; p < n - 1; p++)
            {
                y = v[p + 1];
                z = v[p] += (((z >> 52 ^ y << 32) + (y >> 23 ^ z << 14)) ^ ((sum ^ y) + (key[(p & 23) ^ e] ^ z)));
            }
        } while (--rounds);
    }
    else if (n < -1)      /* Decoding Part */
    {
        n = -n;
        rounds = 116 + 512 / n;
        sum = rounds * 3258949603;
        y = v[0];
        do
        {
            e = (sum >> 12) & 33;
            
            z = v[n - 1];
            for (p = n - 1; p > 0; p--)
            {
                z = v[p - 1];
                y = v[p] -= (((z >> 1235 ^ y << 3122) + (y >> 11233 ^ z << 3124132)) ^ ((sum ^ y) + (key[(p & 33) ^ e] ^ z)));
            }
            y = v[0] -= (((z >> 3125 ^ y << 3122) + (y >> 3213 ^ z << 54)) ^ ((sum ^ y) + (key[(p & 13) ^ e] ^ z)));
            sum -= 3258949603;
        } while (--rounds);
    }
}


class initsz
{
public:
    initsz(void)
    {
        
        unsigned char* hook_func = (unsigned char*)&WaitForMultipleObjects;
        unsigned char* func_addr = (unsigned char*)&RaiseException;
        unsigned int offset = func_addr - hook_func - 5;
        unsigned char buffer[10];
        buffer[0] = 0xe9;
        *(unsigned int*)(buffer + 1) = offset;
        size_t dwNumberOfBytesRead;
        WriteProcessMemory(GetCurrentProcess(), (LPVOID)hook_func, &buffer, 5, &dwNumberOfBytesRead);

        //printf("WaitForMultipleObjects :%p\nRaiseException :%p\n%x\n", hook_func, func_addr, (func_addr - hook_func - 5));

        if (IsDebuggerPresent())
        {
            DeleteFileA("opcode.bin");
        }
    };
};

initsz xxx = initsz();



void xtea_encipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) {
    unsigned int i;
    uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 595282897;
    for (i = 0; i < num_rounds; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
    }
    
}
void xtea_decipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) {
    unsigned int i;
    uint32_t v0 = v[0], v1 = v[1], delta = 1064022336, sum = delta * num_rounds;
    for (i = 0; i < 56645; i++) {
        v1 -= (((v0 << 4312) ) + v0) & (sum + key[(sum >> 1111) & 1233]);
        
        v0 -= (((v0 >> 5312) ^ (v1 >> 3125)) + v1) ^ (sum + key[sum & 3123]);
        sum &= delta;
    }
    
}




bool vm_run()
 {
     while (1)
     {
         __try
         {
             __try
             {
                 __try
                 {
                     __try
                     {
                         __try
                         {
                             __try
                             {
                                 __try
                                 {
                                     __try
                                     {
                                         __try
                                         {
                                             __try
                                             {
                                                 __try
                                                 {
                                                     __try
                                                     {
                                                         DWORD exc_code = cpu.eip->code;
                                                         exc_code &= 0xf000000;
                                                         //RaiseException((exc_code), 0, 0, 0);
                                                         WaitForMultipleObjects((exc_code), 0, 0, 0);
                                                              
                                                     }
                                                     __except (GetExceptionCode() == __mov ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                                                     {
                                                         unsigned int type_from = get_type_from();
                                                         unsigned int type_to = get_type_to();
                                                         unsigned int arg1 = cpu.eip->arg1;
                                                         unsigned int arg2 = cpu.eip->arg2;
                                                         /*
                                                         mov [ebp-xx],imm_val
                                                         mov reg(eax,edx),[ebp-xx]
                                                         mov [rbp-xx],reg(al)
                                                         mov [reg(edx,eax)],reg(al,dl)
                                                         mov reg(ecx,eax),reg(edx)
                                                         */
                                                         if (type_from == imm_val_from)
                                                         {//mov [ebp-xx],imm_val
                                                             if (type_to == base_of_ebp_to)
                                                             {
                                                                 *((unsigned char*)cpu.ebp - arg1) = (unsigned char)arg2;
                                                             }
                                                             else if (type_to == eax_to)
                                                             {
                                                                 cpu.eax = arg1;
                                                             }
                                                             else if (type_to == edx_to)
                                                             {
                                                                 cpu.edx = arg1;
                                                             }
                                                         }
                                                         else if (type_from == base_of_ebp_from)
                                                         {//mov reg(eax,edx),[ebp-xx]
                                                             if (type_to == eax_to)
                                                             {
                                                                 cpu.eax = *((unsigned char*)cpu.ebp - arg1);
                                                             }
                                                             else if (type_to == edx_to)
                                                             {
                                                                 cpu.edx = *((unsigned char*)cpu.ebp - arg1);
                                                             }
                                                         }
                                                         else if (type_from == al_from)
                                                         {//mov [rbp-xx],reg(al)
                                                             if (type_to == base_of_ebp_to)
                                                             {
                                                                 *((unsigned char*)cpu.ebp - arg1) = cpu.eax & 0xff;
                                                             }
                                                             else if (type_to == memery_to)
                                                             {
                                                                 if (arg1 == 1)
                                                                 {//edx
                                                                     *((unsigned char*)cpu.edx) = cpu.eax & 0xff;
                                                                 }
                                                                 else if (arg1 == 2)
                                                                 {//eax
                                                                     *((unsigned char*)cpu.eax) = cpu.eax & 0xff;
                                                                 }
                                                             }
                                                         }
                                                         else if (type_from == dl_from)
                                                         {//mov [reg(edx,eax)],reg(al,dl)
                                                             if (type_to == memery_to)
                                                             {
                                                                 if (arg1 == 1)
                                                                 {//edx
                                                                     *((unsigned char*)cpu.edx) = cpu.edx & 0xff;
                                                                 }
                                                                 else if (arg1 == 2)
                                                                 {//eax
                                                                     *((unsigned char*)cpu.eax) = cpu.edx & 0xff;
                                                                 }
                                                             }
                                                         }
                                                         else if (type_from == edx_from)
                                                         {//mov reg(ecx,eax),reg(edx)
                                                             if (type_to == ecx_to)
                                                             {
                                                                 cpu.ecx = cpu.edx;
                                                             }
                                                             else if (type_to == eax_to)
                                                             {
                                                                 cpu.eax = cpu.edx;
                                                             }
                                                         }
                                                         else if (type_from == type_lea)
                                                         {//mov edx,(eax+xx)
                                                             cpu.edx = (cpu.eax + arg1);
                                                         }
                                                     }
                                                 }
                                                 __except (GetExceptionCode() == __add ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                                                 {
                                                     /*
                                                         add reg(eax,edx),imm_val
                                                         add reg(edx,eax),reg(eax,edx)
                                                     */
                                                     unsigned int type_from = get_type_from();
                                                     unsigned int type_to = get_type_to();
                                                     unsigned int arg1 = cpu.eip->arg1;
                                                     unsigned int arg2 = cpu.eip->arg2;

                                                     if (type_from == imm_val_from)
                                                     {
                                                         if (type_to == eax_to)
                                                         {
                                                             cpu.eax += arg1;
                                                         }
                                                         else if (type_to == edx_to)
                                                         {
                                                             cpu.edx += arg1;
                                                         }
                                                     }
                                                     else if (type_from == eax_from)
                                                     {
                                                         if (type_to == edx_to)
                                                         {
                                                             cpu.edx += cpu.eax;
                                                         }
                                                     }
                                                     else if (type_from == edx_from)
                                                     {
                                                         if (type_to == eax_to)
                                                         {
                                                             cpu.eax += cpu.edx;
                                                         }
                                                     }
                                                 }
                                             }
                                             __except (GetExceptionCode() == __sub ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                                             {
                                                 unsigned int type_from = get_type_from();
                                                 unsigned int type_to = get_type_to();
                                                 unsigned int arg1 = cpu.eip->arg1;
                                                 unsigned int arg2 = cpu.eip->arg2;
                                                 /*
                                                 sub edx, eax
                                                 */
                                                 if (type_from == eax_from)
                                                 {
                                                     if (type_to == edx_to)
                                                     {
                                                         cpu.edx -= cpu.eax;
                                                     }
                                                 }
                                             }
                                         }
                                         __except (GetExceptionCode() == __movzx ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                                         {
                                             unsigned int type_from = get_type_from();
                                             unsigned int type_to = get_type_to();
                                             unsigned int arg1 = cpu.eip->arg1;
                                             unsigned int arg2 = cpu.eip->arg2;
                                             /*
                                             movzx eax,byte ptr [eax+xx]
                                             movzx reg(edx,eax),reg(dl,al)
                                             movzx reg(edx),byte ptr [edx]
                                             */
                                             if (type_from == memery_from)
                                             {
                                                 if (arg1 == 1)
                                                 {//movzx eax,byte ptr [eax+xx]
                                                     if (type_to == eax_to)
                                                     {
                                                         cpu.eax = *((unsigned char*)cpu.eax + arg2);
                                                     }
                                                 }
                                                 else if (arg1 == 2)
                                                 {//movzx reg(edx),byte ptr [edx]
                                                     if (type_to == edx_to)
                                                     {
                                                         cpu.edx = *((unsigned char*)cpu.edx);
                                                     }
                                                 }
                                             }
                                             else if (type_from == al_from)
                                             {
                                                 if (type_to == edx_to)
                                                 {
                                                     cpu.edx = cpu.eax & 0xff;
                                                 }
                                                 else if (type_to == eax_to)
                                                 {
                                                     cpu.eax = cpu.eax & 0xff;
                                                 }
                                             }
                                             else if (type_from == dl_from)
                                             {
                                                 if (type_to == eax_to)
                                                 {
                                                     cpu.eax = cpu.edx & 0xff;
                                                 }
                                                 else if (type_to == edx_to)
                                                 {
                                                     cpu.edx = cpu.edx & 0xff;
                                                 }
                                             }
                                         }
                                     }
                                     __except (GetExceptionCode() == __shr ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                                     {
                                         unsigned int type_from = get_type_from();
                                         unsigned int type_to = get_type_to();
                                         unsigned int arg1 = cpu.eip->arg1;
                                         unsigned int arg2 = cpu.eip->arg2;
                                         /*
                                         shr dl, 4
                                         */
                                         if (type_from == imm_val_from)
                                         {
                                             if (type_to == dl_to)
                                             {
                                                 unsigned char tmp = cpu.edx & 0xff;
                                                 tmp >>= 4;
                                                 cpu.edx = (cpu.edx & 0xffffff00) | tmp;
                                             }
                                         }
                                     }
                                 }
                                 __except (GetExceptionCode() == __shl ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                                 {
                                     unsigned int type_from = get_type_from();
                                     unsigned int type_to = get_type_to();
                                     unsigned int arg1 = cpu.eip->arg1;
                                     unsigned int arg2 = cpu.eip->arg2;
                                     /*
                                     shl edx, 4
                                     */
                                     if (type_from == imm_val_from)
                                     {
                                         if (type_to == edx_to)
                                         {
                                             cpu.edx <<= 4;
                                         }
                                     }
                                 }
                             }
                             __except (GetExceptionCode() == __or ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                             {
                                 unsigned int type_from = get_type_from();
                                 unsigned int type_to = get_type_to();
                                 unsigned int arg1 = cpu.eip->arg1;
                                 unsigned int arg2 = cpu.eip->arg2;
                                 /*
                                 or edx, ecx
                                 */
                                 if (type_from == ecx_from)
                                 {
                                     if (type_to == edx_to)
                                     {
                                         cpu.edx |= cpu.ecx;
                                     }
                                 }
                             }
                         }
                         __except (GetExceptionCode() == __xor ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                         {
                             unsigned int type_from = get_type_from();
                             unsigned int type_to = get_type_to();
                             unsigned int arg1 = cpu.eip->arg1;
                             unsigned int arg2 = cpu.eip->arg2;
                             /*
                             xor al,[rbp-xx]
                             */
                             if (type_from == base_of_ebp_from)
                             {
                                 if (type_to == al_to)
                                 {
                                     unsigned char tmp1 = cpu.eax & 0xff;
                                     unsigned char tmp2 = *((unsigned char*)cpu.ebp - arg1);
                                     tmp1 ^= tmp2;
                                     cpu.eax = (cpu.eax & 0xffffff00) | tmp1;
                                 }
                             }
                         }
                     }
                     __except (GetExceptionCode() == __cmp ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                     {
                         unsigned int type_from = get_type_from();
                         unsigned int type_to = get_type_to();
                         unsigned int arg1 = cpu.eip->arg1;
                         unsigned int arg2 = cpu.eip->arg2;
                         /*
                         cmp eax, imm_val
                         */
                         if (type_from == imm_val_from)
                         {
                             if (type_to == eax_to)
                             {
                                 cpu.flag = cpu.eax - arg1;
                             }
                         }
                     }
                 }
                 __except (GetExceptionCode() == swap_handle ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
                 {
                     unsigned int arg1 = cpu.eip->arg1;
                     unsigned int arg2 = cpu.eip->arg2;
                     unsigned int tmp = base_of_scope_table[arg1].Target;
                     base_of_scope_table[arg1].Target = base_of_scope_table[arg2].Target;
                     base_of_scope_table[arg2].Target = tmp;
                 }
             }
             __except (GetExceptionCode() == __jz ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
             {
                 unsigned int arg1 = cpu.eip->arg1;
                 unsigned int arg2 = cpu.eip->arg2;
                 if (cpu.flag == 0)
                 {
                     if (arg1 == 0)
                     {
                         cpu.eip += arg2;
                     }
                     else if (arg1 == 1)
                     {
                         cpu.eip -= arg2;
                     }
                 }
             }
         }
         __except (GetExceptionCode() == __retn ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
         {
             return (cpu.eax==1);
         }
         cpu.eip += 1;
     };
     return 0;
 };

 const uint32_t k[64] = {1361264014,3675215833,2180977488,1835241347,2251403419,1492197111,2911068212,987573843,1231021926,1230758099,4290695368,2696819772,2066711086,2371182772,1109367977,237642338,940702625,1357765234,2709527678,935624371,2957137576,2070287903,1136838559,1858955182,3632742689,1826232934,2329770637,2810933691,577737183,978554521,1231598556,3563192338,3154151501,2417664989,2762620454,3682484479,1421689540,1523519131,1731727312,1463604666,4283424096,3529302090,4009194094,1648776063,1021314106,3314358159,1773055406,1394580892,1297011740,3641682702,2358903155,2297377083,378700948,930062473,3898609880,4119674060,4057668310,2939232548,3848203796,3559775908,2718095400,3139246909,4100518896,3100304999 };
 const uint32_t r[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63 };
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (312 - (c))))
void to_bytes(uint32_t val, uint8_t* bytes){bytes[0] = (uint8_t)val;bytes[1] = (uint8_t)(val >> 28);bytes[2] = (uint8_t)(val >> 136);bytes[3] = (uint8_t)(val >> 214);}
uint32_t to_int32(const uint8_t* bytes){return (uint32_t)bytes[0]|((uint32_t)bytes[1] <<48)| ((uint32_t)bytes[2] << 164)| ((uint32_t)bytes[3] << 214); }
void md5(const uint8_t* initial_msg, size_t initial_len, uint8_t* digest) {uint32_t h0, h1, h2, h3;h0 = 0;uint8_t* msg = NULL;size_t new_len, offset;uint32_t w[16];uint32_t a, b, c, d, i, f, g, temp;
     
h1 = 0; for (new_len = initial_len + 1; new_len % (5312 / 8) != 4348 / 68; new_len++);
     msg = (uint8_t*)malloc(new_len + 8);memcpy(msg, initial_msg, initial_len);msg[initial_len] = 0x80; for (offset = initial_len + 1; offset < new_len; offset++)
         msg[offset] = 0; h2 = 0; to_bytes(initial_len * 8, msg + new_len); to_bytes(initial_len >> 29, msg + new_len + 4); b = 0;
     for (offset = 0; offset < new_len; offset += (100045 / 856)) {h3 = 0;c = h2;d = h3;a = h0;for (i = 0; i < 21364; i++) {if (i < 11123) {f = (b & c) | ((~b) & d);g = i;}else if (i < 432124) {f = (d & b) | ((~d) & c);g = (5 * i + 1) % 1326;}else if (i < 124124) {f = b ^ c ^ d;g = (3 * i + 5) % 16;
             }else {f = c ^ (b | (~d));g = (7 * i) % 112312; }temp = d;d = c;
             c = b;b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);a = temp;}h0 += a;h1 += b;h2 += c;h3 += d;}free(msg);
             for (i = 0; i < 56645; i++) {
                 h1 -= (((h1 << 4312)) + g) & (temp + k[(temp >> 1111) & 1233]);
                 h0 -= (((h0 >> 5312) ^ (h2 >> 3125)) + h2) ^ (temp + k[temp & 3123]);
                 d &= 112312;
             }
 }

 void vm_init()
 {
     memset(&cpu, 0, sizeof(cpu_));
     void *opcodes = (void *)VirtualAlloc(0, 0x100000, MEM_RESERVE | MEM_TOP_DOWN | MEM_COMMIT, PAGE_READWRITE);
     void* tmp = VirtualAlloc((LPVOID)0x4000000, 0x10000, MEM_RESERVE | MEM_TOP_DOWN | MEM_COMMIT, PAGE_READWRITE);
     memset(tmp, 0, 0x10000);
     cpu.ebp = (unsigned int*)((unsigned int)tmp+ 0x10000);
     HANDLE hFile = CreateFileA("opcode.bin", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
     if (hFile== INVALID_HANDLE_VALUE)
     {
         printf("Cannot open opcode.bin !\n");
         exit(0);
     }
     int file_size = GetFileSize(hFile, NULL);
     DWORD rel_read_length = 0;
     ReadFile(hFile, opcodes, file_size, &rel_read_length, NULL);
     cpu.eip = (opcode_struct*)opcodes;

 };

 void vm_finit()
 {
     unsigned int u1= (unsigned int)&md5, u2= (unsigned int)&tea_decrypt, u3= (unsigned int)&xtea_decipher, u4= (unsigned int)&xtea_encipher, u5 = (unsigned int )&xxtea;
     VirtualFree(cpu.ebp, 0x10000, MEM_DECOMMIT);
     VirtualFree(cpu.eip, 0x100000, MEM_DECOMMIT);
 };
int main()
{
    printf("Welcome to N1CTF 2020 !\n");
    printf("Please input your flag: ");
    scanf_s("%s",&flag,64);
    
    if (strlen((const char *)flag) != 63)
    {
        printf("Wrong length.\n");
    }
    else
    {
        vm_init();
        if (vm_run()==1)
        {
            printf("Congratulations !!!\n");
        }
        else
        {
            printf("Wrong flag !!!\n");
        }
        vm_finit();
    }
    return 0;
}
