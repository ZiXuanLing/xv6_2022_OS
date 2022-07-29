#include "../include/asm.h"
#include "../include/memlayout.h"
#include "../include/mmu.h"
#include "../include/param.h"

.p2align 2
.text
.global multiboot_header:
    #define magic 0x1badb001
    #define flags 0
    .long magic
    .long flags
    .long (-magic-flags)

.global _start
_start = V2P_WO(entry)  // 全局符号，指向entry入口地址

.global entry
entry:
    movl %cr4, %eax  // 使用大页模式
    orl $(CR4_PSE), %eax
    movl %eax, %cr4

    movl $(V2P_WO(entrypgdir)), %eax
    movl %eax, %cr3

    movl %cr0, %eax
    orl $(CR0_PG | CR0_WP), %eax
    movl %eax, %cr0

    movl $(stack + KSTACKSIZE), %esp  // 设置堆栈指针

    movl $main, %eax
    jmp * %eax

.comm stack, KSTACKSIZE
