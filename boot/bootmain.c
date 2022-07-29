/**
 * @file bootmain.c
 * @author liuhao(liuhaopat@qq.com)
 * @brief 从硬盘中读出xv6的kernel文件到内存，然后跳到入口点开始执行kernel代码
 * @version 0.1
 * @date 2022-07-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/types.h"
#include "../include/elf.h"
#include "../include/x86.h"
#include "../include/memlayout.h"

#define SECTSIZE 512  // 一个扇区大小为512B

void bootmain(void) {
    struct elfhdr *elf; // 内核是ELF格式文件
    struct proghdr *ph, *eph;  // 程序头表
    void (*entry) (void); // ELF入口地址
    uchar *pa; 

    elf = (struct elfhdr *) 0x10000;
    
    readseg((uchar *)elf, 4096, 0); 

    if (elf->magic != ELF_MAGIC)  {
        return ;
    }

    ph = (struct proghdr *)((uchar *)elf + elf->phoff);
    eph = ph + elf->phnum;
    for (; ph < eph; ph ++) {
        pa = (uchar *)ph->paddr;
        readseg(pa, ph->filesz, ph->off);
        if (ph->memsz > ph->filesz) {
            stosb(pa + ph->filesz, 0, ph->memsz - ph->filesz);
        }
    }

    entry = (void (*)(void))(elf->entry);
    entry(); // 跳转到entry的入口地址
}

void readsect(void *dst, uint offset) {
    waitdisk();

    outb(0x1F2, 1); 
    outb(0x1F3, offset);  // LBA模式的0~7位
    outb(0x1F4, offset >> 8);
    outb(0x1F5, offset >> 16);
    outb(0x1F6, offset >> 24 | 0xE0);
    outb(0x1F7, 0x20);

    waitdisk();
    insl(0x1F0, dst, SECTSIZE / 4); // 从I/O读入一个扇区数据
}

/**
 * @brief 读磁盘数据，offset为偏移
 * 
 * @param pa 
 * @param count 
 * @param offset 
 */
void readseg(uchar *pa, uint count, uint offset) {
    uchar *epa;
    epa = pa + count;
    
    pa -= offset % SECTSIZE; // 消除扇区边界

    offset = (offset / SECTSIZE) + 1; // 扇区1为启动扇区

    for (; pa < epa; pa += SECTSIZE, offset) {
        readsect(pa, offset);
    }

}