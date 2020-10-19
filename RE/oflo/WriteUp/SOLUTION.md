#### SOLUTION



1. 64 位 ELF

2. 中间加了几条花指令，使用了 3 种花指令，nop 掉重新反编译即可

   ```c
   // call 之后改变栈顶返回地址 使用了模式展开
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
   
   // 重叠指令
   #define FlowerCode1 \
   	asm(".byte 0xEB;"	\
   		".byte 0xFF;"	\
   		".byte 0xC0;"	\
   		".byte 0x48;"	\
   		".byte 0x90;"	\
   		".byte 0x90;"	\
   	);
   
   // 简单的两个跳转分支
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
   ```

6. `sub_4008B9` 函数执行了 `fork`、`wait`、`execve`，执行了 `cat /proc/version` 命令，并通过 `ptrace`，使父进程得到子进程的输出。

4. 获取输入后，用输入前 5 位异或解密某一函数前 10 个字节，可通过常用函数开头的 5 个字节解得前 5 个字符，也可直接猜到 `n1ctf`。用 IDAPython 或 IDC 脚本 patch 一下即可。也就是说这个输入正确才能正确运行函数。

5. 很简单的异或运算判断。

6. 静态分析挺丑的，但是只要动调起来了挺简单的（IDA 动调记得关异常提示什么的）

7. 是一个最近看的短小东西改的，感觉不太精妙呜呜
