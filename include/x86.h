#ifndef __INCLUDE_X86_H__
#define __INCLUDE_X86_H__


#include "types.h"

// x86内联汇编

static inline uchar inb(ushort port) {
    uchar data;

    asm volatile (
        "in %1, %0"
        : "=a" (data)  // output
        : "d" (port) // port
    );
    return data;
}

/**
 * @brief 从端口port连续读入cnt个整数(4B)
 * 
 * @param port 
 * @param addr 
 * @param cnt 
 */
static inline void insl(int port, void *addr, int cnt) {
    asm volatile (
        "cld\n\trep insl"
        : "=D" (addr), "=c" (cnt)
        : "d" (port), "0" (addr), "1" (cnt)
        : "memory", "cc"
    );
}

static inline void outb(ushort port, uchar data) {
    asm volatile (
        "out %0, %1"
        :: "a" (data), "d" (port)
    );
}

static inline void outw(uchar port, ushort data) {
    asm volatile (
        "out %0, %1"
        :: "a" (data), "d" (port)
    );
}

static inline void outsl(int port, const void *addr, int cnt) {
    asm volatile (
        "cld\n\trep outsl"
        : "=S" (addr), "=c" (cnt)
        : "d" (port), "0" (addr), "1" (cnt)
        : "cc"
    );
}

static inline void stosb(void *addr, int data, int cnt) {
    asm volatile (
        "cld\n\trep stosb"
        : "=D" (addr), "=c" (cnt)
        : "0" (addr), "1" (cnt), "a" (data)
        : "memory", "cc"
    );
}

static inline void cli(void) {
    asm volatile (
        "cli"
    );
}

static inline void sti(void) {
    asm volatile (
        "sli"
    );
}

static inline uint xchg(volatile uint *addr, uint newval) {
    uint result;

    asm volatile (
        "lock\n\txchgl %0, %1"
        : "+m" (*addr), "=a" (result)
        : "1" (newval)
        : "cc"
    );

    return result;
}

struct trapframe {
    uint edi;
    uint esi;
    uint ebp;
    uint ebx;
    uint edx;
    uint ecx;
    uint eax;

    ushort gs;
    ushort padding;
    ushort fs;
    ushort padding;
    ushort es;
    ushort padding;
    ushort ds;
    ushort padding;
    uint trapno;  

    uint err;
    uint eip;
    ushort cs;
    ushort padding;
    uint eflags;

    uint esp;
    ushort ss;
    ushort padding;
};

#endif