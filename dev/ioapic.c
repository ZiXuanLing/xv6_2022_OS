#include "../include/types.h"
#include "../include/defs.h"
#include "../include/traps.h"

#define IOAPIC 0xFEC00000

#define REG_ID    0x00
#define REG_VER   0x01
#define REG_TABLE 0x10

#define INT_DISABLE   0x00010000
#define INT_LEVEL     0x00008000
#define INT_ACTIVELOW 0x00002000
#define INT_LOGOCAL   0X00000800

struct ioapic {
    uint reg; // 0xEFC0xy00
    uint pad[3];
    uint data;   // 地址偏移16 0xFEC0xy00
};

volatile struct ioapic *ioapic;

static uint ioapicread(int reg) {
    ioapic->reg = reg;
    return ioapic->data;
}

static void ioapicwrite(int reg, uint data) {
    ioapic->reg = reg;
    ioapic->data = data;
}

void ioapicinit(void) {
    int i, id, maxintr;

    if (!ismp) { // ISMP表示多核, 在mp模块中可知
        return;
    }

    ioapic = (volatile struct ioapic *) IOAPIC;

    maxintr = (ioapicread(REG_VER) >> 16) & 0xFF; // 版本信息中有最大中断数量信息
    id = ioapicread(REG_ID) >> 24; 
    if (id != ioapicid) {
        // 
    }

    // 全部中断设为边沿、高有效和屏蔽
    for (i = 0; i < maxintr; ++ i) {
        // RTE有64位，分两次写
        ioapicwrite(REG_TABLE + 2 * i, INT_DISABLE | (T_IRQ0 + i));  // 中断向量号其实值是T_IRQ0 = 32

        ioapicwrite(REG_TABLE + 2 * i + 1, 0);
    }

}

void ioapicenable(int irq, int cpunum) {
    if (!ismp) {
        return;
    }
    ioapicwrite(REG_TABLE + 2 * irq, T_IRQ0 + irq);
    ioapicwrite(REG_TABLE + 2 * irq + 1, cpunum << 24); // 设置传送的CPU ID
}