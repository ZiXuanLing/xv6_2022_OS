/**
 * @file proc.c
 * @author your name (you@domain.com)
 * @brief 进程调度
 * @version 0.1
 * @date 2022-07-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/types.h"
#include "../include/defs.h"
#include "../include/memlayout.h"
#include "../include/mmu.h"
#include "../include/x86.h"
#include "../include/proc.h"
#include "../include/spinlock.h"
#include "../include/param.h"

struct {
    struct spinlock lock;
    struct proc proc[NPROC];
} ptable;  // 全局进程管理数据结构

static struct proc *initproc; // init进程的指针

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

void pinit(void) {
    initlock(&ptable.lock, "ptable");
}

/**
 * @brief 分配进程控制块病初始化内核栈
 * 
 * @return struct proc* 
 */
static struct proc* allocproc(void) {
    struct proc *p;
    char *sp;

    for (p = ptable.proc; p < &ptable.proc[NPROC]; p ++) {
        if (p->state == UNUSED) {
            goto found;
        }
    }
    return 0;

found:
    p->state = EMBRYO; // 状态初始化为胚胎
    p->pid = nextpid ++;

    if ((p->kstack = kalloc()) == 0) {
        p->state = UNUSED;
        return 0;
    }
    sp = p->kstack + KSTACKSIZE; // 堆栈指针指向栈底

    sp -= sizeof *p->tf;
    p->tf = (struct trapframe *)sp;

    sp -= 4; // 
    *(uint *)sp = (uint)trapret; // 用于保存trapret

    sp -= sizeof *p->context;
    p->context = (struct context *)sp;
    memset(p->context, 0, sizeof *p->context);
    p->context->eip = (uint)forkret; // 本进程的context中只有eip指向forkret

    return p;
}

/**
 * @brief 创建第一个用户态进程
 * 
 */
void userinit(void) {
    
}
