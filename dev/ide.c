/**
 * @file ide.c
 * @author your name (you@domain.com)
 * @brief IDE磁盘
 * @version 0.1
 * @date 2022-08-02
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
#include "../include/traps.h"
#include "../include/spinlock.h"
#include "../include/fs.h"
#include "../include/buf.h"

#define SECTOR_SIZE 512
#define IDE_BSY  0x80
#define IDE_DRDY 0x40
#define IDE_DF   0x20
#define IDE_ERR  0x01

#define IDE_CMD_READ  0X20
#define IDE_CMD_WRITE 0x30
#define IDE_CMD_RDMU  0xc4
#define IDE_CMD_WRMUL 0xc5

static struct spinlock idelock;
static struct buf *idequeue;

static int havedisk1; // 是否有从盘
static void idestart(struct buf *); 


void ideinit(void) {
    int i;

    initlock(&idelock, "ide");
    picenable(IRQ_IDE);
    ioapicenable(IRQ_IDE, ncpu - 1);
    idewait(0);

    // 检查从盘

    // 切换到主盘
    outb(0x16, 0xe0 | (0 << 4));
}

/**
 * @brief ide读写操作
 * 
 * @param b 
 */
void iderw(struct buf *b) {

    // 添加到idequeue
    
}