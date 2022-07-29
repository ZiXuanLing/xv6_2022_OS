#include "../include/mmu.h"

.global alltraps // 公共入口，以TF中的trapno相互区分
alltraps:
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    pushal

    movw $(SEG_KDATA << 3), %ax  // ds和es都使用内核数据段SEG_KDATA
    movw %ax, %ds
    movw %ax, %es

    movw $(SEG_KCPU << 3), %ax // fs和gs都使用per-CPU段SEG_KCPU
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp
    call trap
    addl $4, %esp

.global trapret  // 公共返回代码
trapret:
    popl %ds
    popl %es
    popl %fs
    popl %gs
    popal
    addl $0x8, %esp
    iret