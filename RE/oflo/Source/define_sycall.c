#include <stdio.h>
#include <asm/unistd_64.h>
#include <sys/types.h>
#include <sys/reg.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>


#define __syscall0(type,name) 	\
type name()	\
{	\
	long ret;	\
	__asm__ volatile (	\
		"syscall"	::	"a" (__NR_##name));	\
		asm("mov %%rax, %0"	: "=r"(ret));	\
	return (type)ret;	\
}

#define __syscall1(type,name,type1,arg1) \
type name(type1 arg1)	\
{ \
	long ret;	\
	__asm__ volatile (		\
		"syscall"	::	"a"	(__NR_##name), "g"((type1)(arg1)));\
		asm("mov %%rax, %0" : "=r"(ret));	\
	return (type)ret;	\
}

#define __syscall2(type,name,type1,arg1, type2, arg2) \
type name(type1 arg1, type2 arg2)	\
{ \
	long ret;	\
	__asm__ volatile (		\
		"syscall"	::	"a"	(__NR_##name), "g"((type1)(arg1)), "g"((type2)(arg2)));\
		asm("mov %%rax, %0" : "=r"(ret));	\
	return (type)ret;	\
}

#define __syscall3(type,name,type1,arg1,type2,arg2,type3,arg3) \
type name(type1 arg1,type2 arg2,type3 arg3) \
{ \
    long ret; \
    __asm__ volatile (      \
        "syscall" :: "a" (__NR_##name), "g"((type1)(arg1)), "g"((type2)(arg2)), \
        			"g"((type3)(arg3)));\
    asm("mov %%rax, %0" : "=r"(ret));                 \
    return (type)ret; \
}

#define __syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) \
type name(type1 arg1,type2 arg2,type3 arg3,type4 arg4) \
{ \
    long ret; \
    __asm__ volatile (      \
        "syscall" :: "a" (__NR_##name), "g"((type1)(arg1)), "g"((type2)(arg2)),	\
        			 "g"((type3)(arg3)), "g"((type4)(arg4)));\
    asm("mov %%rax, %0" : "=r"(ret));                 \
    return (type)ret; \
}

#define __syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5) \
type name(type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5) \
{ \
    long ret; \
    __asm__ volatile (      \
        "syscall" :: "a" (__NR_##name), "g"((type1)(arg1)), "g"((type2)(arg2)),	\
        			 "g"((type3)(arg3)), "g"((type4)(arg4)), "g"((type5)(arg5)));\
    asm("mov %%rax, %0" : "=r"(ret));                 \
    return (type)ret; \
}

#define __syscall6(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5,type6,arg6) \
type name(type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5,type6 arg6) \
{ \
    long ret; \
    __asm__ volatile (      \
        "syscall" :: "a" (__NR_##name), "g"((type1)(arg1)), "g"((type2)(arg2)),	\
        			 "g"((type3)(arg3)), "g"((type4)(arg4)), "g"((type5)(arg5)),	\
        			 "g"((type6)(arg6)));\
    asm("mov %%rax, %0" : "=r"(ret));                 \
    return (type)ret; \
}

__syscall1(ssize_t, exit, int, status);
__syscall3(ssize_t, write, int, fd, const void *, buf, size_t, count);
__syscall3(ssize_t, read, int, fd, const void *, buf, size_t, count);
__syscall0(pid_t, fork);
__syscall3(int, execve, const char *, filename, char *const *, argv, char *const *, envp);
__syscall4(pid_t, wait4, pid_t, pid, int *, status, int, option, struct rusage *, ru);
__syscall1(int, close, int, fd);
__syscall1(void, success, char, xor);
__syscall3(int, mprotect, void *, addr, size_t, len, int, prot);

//查看man syscall可以看到，x86-64和32，发现参数的顺序思rdi rsi rdi r10 r8 r9这样的顺序，不能变。
//syscall指令的调用指令是rax，返回值也是rax


#define FlowerCode0(i)	\
	asm("call func" #i ";"	\
		".byte 0xE8;"	\
		"jmp l" #i ";"	\
		"func" #i ":"	\
		"pop %rax ;"	\
		"add $1, %rax ;"	\
		"push %rax ;"	\
		"mov %rsp, %rax ;"	\
		"xchg (%rax), %rax ;"	\
		"pop %rsp ;"	\
		"mov %rax, (%rsp) ;"	\
		"ret ;"	\
		"l" #i ":"	\
	);

#define FlowerCode1 \
	asm(".byte 0xEB;"	\
		".byte 0xFF;"	\
		".byte 0xC0;"	\
		".byte 0x48;"	\
		".byte 0x90;"	\
		".byte 0x90;"	\
	);

#define FlowerCode2	\
	asm(".byte 0x74;"	\
		".byte 0x07;"	\
		".byte 0x75;"	\
		".byte 0x05;"	\
		".byte 0xE9;"	\
		".byte 0x00;"	\
		".byte 0x10;"	\
		".byte 0x40;"	\
		".byte 0x00;"	\
	);


const int long_size = sizeof(long);
void getdata(pid_t pid, long addr, char * str, long sz)
{
	int i = 0, j = sz / long_size;
	char *s = str;
	while (i < j) {
		*(long *)(s + i * 4) = ptrace(PTRACE_PEEKDATA, pid, addr + i * 4, NULL);
		++ i;
	}
	j = sz % long_size;
	if (j != 0) {
		*(long *)(s + i * 4) = ptrace(PTRACE_PEEKDATA, pid, addr + i * 4, NULL);	
	}
}

int my_cat_ver_func(char * str)
{
	pid_t pid;
	int status;
	
	if ((pid = fork()) < 0)
		status = -1;
	if (pid == 0) {
		char *argv[] = {"cat","/proc/version", NULL};
		char *envp[] = {NULL};
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execve("/bin/cat", argv, envp);
		exit(127);
	} else {
		int toggle = 0;
		char *ss = str;
		while (1) {
			wait4(pid, &status, 0, 0);
			if (((status) & 0x7f) == 0)	// WIFEXITED(status)
				break;
			long orig_rax = ptrace(PTRACE_PEEKUSER, pid, 8 * ORIG_RAX, NULL);
			if (orig_rax == SYS_write) {	// write(1, "write\n", 6);
				if (toggle == 0) {
					toggle = 1;
					long addr = ptrace(PTRACE_PEEKUSER, pid, 8 * RSI, NULL);
					long sz = ptrace(PTRACE_PEEKUSER, pid, 8 * RDX, NULL);
					getdata(pid, addr, ss, sz);
					ss += sz;
				}
				else {
					toggle = 0;
				}
			}
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		}
	}
	// write(1, str, (ss - str)); write(1, "\n", 1);
	
	return status;
}

void (*Check)(char*,char*);
int check(char * str, char * input)
{
	char cmp[] = {0x35, 0x2D, 0x11, 0x1A, 0x49, 0x7D, 0x11, 0x14, 0x2B, 0x3B, 0x3E, 0x3D, 0x3C, 0x5F};

	FlowerCode2;	
	
	for (int i = 0; i < 14; ++i) {
		if (cmp[i] != (input[i] ^ 2 + str[i])) {
			FlowerCode0(2);
			return 0;
		}
	}
	return 1;
}

void main(){

	char str[0x200] = {0}, input[0x20] = {0};

	FlowerCode1;
	FlowerCode0(0);	

	if (my_cat_ver_func(str) == -1) {
		exit(0);	
	}
	
	read(0, input, 19);

	unsigned long Addr = (unsigned long)check;
	Check = (void(*)(char*,char*)) Addr;
	mprotect((unsigned int *)((unsigned int)&main & 0xffffc000), 0x10, 7);
	for (int i = 0; i < 10; ++i) {
		*((unsigned char*)Check + i) ^= input[i % 5];
	}
	
	FlowerCode0(1);

	if (check(str, input + 5) != 0) {
		write(1, "Cong!\n", 6); // write(1, "hhh\n", 4);
	}
	
	FlowerCode1;
	
	// write(1, "I am payload who has hijacked your process!\n", 48);
    exit(0);
}
