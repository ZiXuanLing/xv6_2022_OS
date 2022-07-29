### x86.h

**访问硬件(内联汇编)**

不做过多概述

**tramframe**

当用户代码的执行流被内核代码执行流所中断时，此时用户进程的执行流断点现场将保存在一个称为 `trapframe`的陷阱帧中。

主要有几个部分

- 硬件中断会在堆栈中压入 `ss`、`esp`、`eflags`、`cs`和 `ip`寄存器
- 异常会压入 `error code`
- 压入中断号 `trapno`
- 在进入中断处理公共入口之后会压入 `eax ecx edx ebx oesp ebp esi edi`寄存器

在系统调用中，通过调用 `trap()`函数，将进行任务分发，根据堆栈 `trapframe`里保存的中断号 `trapno`转入到相应函数去处理

如果中断（或系统调用）是在内核态发生的，则 `trapframe`顶部没有 `ss`和 `esp`两项，直接从 `eflags开始`

### types.h

自定义数据类型别名设置

### asm.h

`SEG_NULLASM`创建全空的段描述符，以及定制的段描述符 `SEG_ASM`，这两个宏在 `bootloader`中用于构建 `GDT`表中的内容，以便进入保护模式。

另外有关段属性（标志位）的宏。
