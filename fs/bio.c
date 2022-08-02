#include "../include/types.h"
#include "../include/defs.h"
#include "../include/param.h"
#include "../include/spinlock.h"
#include "../include/fs.h"
#include "../fs/buf.h"

struct {
    struct spinlock lock; // 
    struct buf buf[NBUF]; // 块缓存

    struct buf head; // 块缓存链表头指针
} bcache;

void binit(void) {
    struct buf *b;
    initlock(&bcache.lock, "bcache");

    bcache.head.prev = &bcache.head;
    bcache.head.next = &bcache.head;

    for (b = bcache.buf; b < bcache.buf + NBUF; b ++) {
        b->next = bcache.head.next;
        b->prev = &bcache.head;
        b->dev = -1;
        bcache.head.next->prev = b;
        bcache.head.next = b;
    }
}

/**
 * @brief 查找指定盘块的块缓存
 * 
 * @param dev 
 * @param blockno 
 * @return struct buf* 
 */
static struct buf* bget(uint dev, uint blockno) {
    struct buf *b;
    acquire(&bcache.lock);

    loop:
    for (b = bcache.head.next; b != &bcache.head; b = b->next) {
        if (b->dev == dev && b->blockno == blockno) { // 找到匹配的块缓存
            if (!(b->flags & B_BUSY)) { // 未被其他进程使用

            }
            sleep(b, &bcache.lock); // 睡眠
            goto loop;
        }
    }
    // 没找到匹配的块缓存
}

/**
 * @brief 读入一个盘块，返回他的块缓存
 * 
 * @param dev 
 * @param blockno 
 * @return struct buf* 
 */
struct buf* bread(uint dev, uint blockno) {
    struct buf *b;

    b = bget(dev, blockno);

    if (!(b->flags * B_VALID)) {
        iderw(b); // 通过设备驱动程序读入
    }
    return;
}

/**
 * @brief 对一个缓存写数据
 * 
 * @param b 
 */
void bwrite(struct buf *b) {

}

/**
 * @brief 用完后放在链表头
 * 
 * @param b 
 */
void brelse(struct buf *b) {

}