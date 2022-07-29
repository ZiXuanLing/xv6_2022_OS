#ifndef __INCLUDE_MEMLAYOUT_H__

#define __INCLUDE_MEMLAYOUT_H__

#include "types.h"

#define EXTMEM 0x100000  // 扩展内存
#define PHYSTOP 0xE000000  // 物理内存上限
#define DEVSPACE 0xFe000000  // 设备使用的物理内存起始地址

#define KERNBASE 0x80000000  // 内核起点
#define KERNLINK (KERNBASE + EXTMEM)  // 内核的链接地址

#define V2P(a) (((uint)(a)) - KERNBASE)
#define P2V(a) (((void *)(a)) + KERNBASE)

#define V2P_WO(x) ((x) - KERNBASE)
#define P2V_WO(x) ((x) + KERNBASE)

#endif