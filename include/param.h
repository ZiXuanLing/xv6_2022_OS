#ifndef __INCLUDE_PARAM_H__

#define __INCLUDE_PARAM_H__

// xv6系统常数

#define NPROC 64 
#define KSTACKSIZE 4096
#define NCPU 8
#define NOFILE 16
#define NFILE 100
#define NINODE 50
#define NDEV 10
#define ROOTDEV 1
#define MAXARG 32
#define MAXOPBLOCKS 10
#define LOGSIZE (MAXOPBLOCKS * 3)
#define NBUF (MAXOPBLOCKS * 3)
#define FSSIZE 1000

#endif