#include "../include/asm.h"
#include "../include/memlayout.h"
#include "../include/mmu.h"

.code16
.global start
start:
    cli

    xorw %ax, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss

seta20.1:
    inb $0x64, %al
    testb $0x2, %al
    jnz seta20.1

    movb $0xdl, %al
    outb %al, $0x64

seta20.2:
    inb $0x64, %al
    testb $0x2, %al
    jnz seta20.2

    movb $0xdf, %al
    outb %al, $0x60

    lgdt gdtdesc
    movl %cr0, %eax
    orl $SR0_PE, %eax
    movl %eax, %cr0

    ljmp $(SEG_KCODE << 3), $start32

.code32
start32:
    movw $(SEG_KDATA << 3), %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw $0, %ax
    movw %ax, %gs
    movw %ax, %fs

    movl $start, %esp
    call bootmain

    movw $0x8a00, %ax
    movw %ax, %dx
    outw %ax, %dx
    movw $0x8ae0, %ax
    outw %ax, %dx

spin:
    jmp spin

.p2align 2
gdt:
    SEG_NULLASM
    SEG_ASM(STA_X | STA_R, 0x0, 0xffffffff)
    SEG_ASM(STA_W, 0x0, 0xffffffff)

gdtdesc:
    .word (gdtdesc - gdt - 1)
    .long gdt
