#ifndef __INCLUDE_FS_H__


#define __INCLUDE_FS_H__

#define ROOTINO 1
#define BSIZE 512   

struct superblock {
    uint size; // 文件系统的盘块总数
    uint nblocks; // 用于文件数据的盘块数量
    uint ninodes; // 索引节点总数
    uint nlog; // 日志区的盘块总数
    uint logstart; // 日志区起始盘块号
    uint inodestart; // 索引节点区的起始盘块号
    uint bmapstart; // 位图区的起始盘块号
};

#define NDIRECT 12
#define NINDIRECT (BSIZE / sizeof(uint))
#define MAXFILE (NDIRECT + NINDIRECT)

struct inode {
    short type;  // 文件类型
    short major;  // 主设备号
    short minor; // 
    short nlink; // 链接数量
    uint size; // 文件大小
    uint addr[NDIRECT + 1]; // 数据块地址
};

#define IPB (BSIZE / sizeof(struct dinode))

#define IBLOCK(i, sb) ((i) / IPB + sb.innodestart)

#define BPB (BSIZE * 8)

#define BBLOCK(b, sb) (b / BPB + sb.bmapstart)

#define DIRSIZ 14

struct dirent {
    ushort inum;
    char name[DIRSIZE];
};

#endif