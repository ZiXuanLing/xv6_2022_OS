#include "../include/param.h"
#include "../include/types.h"
#include "../include/defs.h"
#include "../include/date.h"
#include "../include/memlayout.h"
#include "../include/traps.h"
#include "../include/mmu.h"
#include "../include/x86.h"
#include "../include/proc.h"

volatile uint *lapic;

#define SVR (0X00F0/4)

static void lapicw(int index, int value) {
    lapic[index] = value;
    // lapic[ID]; 
}

void lapicinit(void) {
    if (!lapic) {
        return; 
    }
    // lapicw(SVR, );
}