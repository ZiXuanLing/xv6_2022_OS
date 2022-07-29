/**
 * @file main.c
 * @author liuhao(liuhaopat@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/types.h"
#include "../include/defs.h"
#include "../include/param.h"
#include "../include/memlayout.h"
#include "../include/mmu.h"
#include "../include/proc.h"
#include "../include/x86.h"

static void startothers(void);
static void mpmain(void) __attribute__((noreture));
extern pde_t *kpgdir;
extern char end[];

int main(void) {
    kinit1(end, P2V(4 * 1024 * 1024)); // end是ELF kernel结束地址
    kvmalloc(); // 内核页表
}
__attribute__((__aligned__(PGSIZE))) // 页边界对齐
pde_t entrypgdir[NPDENTRIES] = {
    [0] = (0) | PTE_P | PTE_W | PTE_PS, // 0-4MB虚地址
    [KERNBASE >> PDXSHIFT] = (0) | PTE_P | PTE_W | PTE_PS, // 0x80000000-虚地址
};