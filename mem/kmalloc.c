#include "../include/types.h"
#include "../include/defs.h"
#include "../include/param.h"
#include "../include/memlayout.h"
#include "../include/mmu.h"
#include "../include/spinlock.h"

void freerange(void *vstart, void *vend);
extern char end();

struct run {
    struct run *next;
};

struct {
    struct spinlock lock;
    int use_lock;
    struct run *freelist; // netx指针
} kmem;

void kinit1(void *vstart, void *vend) {
    initlock(&kmem.lock, "kmem"); // 创建一个用于管理空闲页帧链表的锁
    kmem.use_lock = 0;
    freerange(vstart, vend);
}

void kinit2(void *vstart, void *vend) {
    freerange(vstart, vend);
    kmem.use_lock = 1;
}

void freerange(void *vstart, void vend) {
    char *p;
    p = (char *)PGROUNDUP((uint) vstart);  // 讲地址转换页边界
    for (; p + PGSIZE <= (char *)vend; p += PGSIZE) {
        kfree(p); // 回收一个页帧
    }
}

/**
 * @brief 释放虚地址v指向的物理页帧
 * 
 * @param v 
 */
void kfree(char *v) {
    struct run *r;

    if ((uint)v % PGSIZE || v < end || V2P(v) >= PHYSTOP) {  // 页边界对齐且不越界
        panic("kfree");
    }

    memset(v, 1, PGSIZE);

    if (kmem.use_lock) {
        acquire(&kmem.lock);
    }
    r = (struct run *) v;  // 将页帧插入到链表头部
    r->next = kmem.freelist;
    kmem.freelist = r;
    if (kmem.use_lock) {
        release(&kmem.lock);
    }
}

char *kalloc(void) {
    struct run *r;
    if (kmem.use_lock) {
        acquire(&kmem.lock);
    }
    r = kmem.freelist;  // 从链表头部取一个空闲页帧
    if (r) {
        kmem.freelist = r->next;  // 链表头后移到下一个空闲链表
    }
    if (kmem.use_lock) {
        release(&kmem.lock);
    }
    return (char *)r;
}