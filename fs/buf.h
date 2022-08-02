#include "../include/types.h"
#include "../include/fs.h"

struct buf {
    int flags;
    uint dev; // 设备号
    uint blockno; // 对应的盘块号
    struct buf *prev;
    struct buf *next;
    struct buf *qnext; // 所在的磁盘I/O调度队列
    uchar data[BSIZE]; // 所在的盘块数据，一般为一个块大小
};

#define B_BUSY 