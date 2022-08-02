#include "../include/types.h"
#include "../include/defs.h"
#include "../include/param.h"
#include "../include/traps.h"
#include "../include/spinlock.h"
#include "../include/fs.h"
#include "../include/file.h"
#include "../include/mmu.h"
#include "../include/proc.h"
#include "../include/x86.h"

static void consputc(int);

static int panicked = 0;

static struct {
    struct spinlock lock;
    int locking;
} cons;

static void printint(int xx, int base, int sign) {
    static char digits[] = "0123456789abcdef";
    char buf[16]; 
    int i;
    uint x;

    if (sign && (sign = xx < 0)) {
        x = -xx;
    }
    else {
        x = xx;
    }

    i = 0;
    do {
        buf[i ++] = digits[x % base];
    }
    while ((x / base) != 0);

    if (sign) {
        buf[i ++] = '-';
    }

    while (-- i >= 0) {
        consputc(buf[i]);
    }
}

/**
 * @brief 实现%d %x % %s
 * 
 * @param fmt 
 * @param ... 
 */
void cprintf(char *fmt, ...) {
    int i, c, locking;
    uint *argp;
    char *s;

    locking = cons.locking;
    if (locking) {
        acquire(&cons.lock);
    }

    if (fmt == 0) {
        panic("null fmt");
    }

    argp = (uint *)(void *)(&fmt + 1);
    for (i = 0; (c = fmt[i] & 0xff) != 0; ++ i) {
        if (c != '%') {
            consputc(c);
            continue;
        }
        c = fmt[++ i] & 0xff;
        if (c == 0) {
            break;
        }
        switch (c) {
            case 'd':
                printint(* argp ++, 10, 1);
                break;
            case 'x':
            case 'p':
                printint(* argp ++, 16, 1);
                break;
            case 's':
                break;
            case '%':
                consputc('%');
                break;
            default:
                consputc('%');
                consputc(c);
                break;
        }
    }
    if (locking) {
        release(&cons.lock);
    }
}

void panic(char *s) {
    int i;
    uint pcs[10];

    cli();
    cons.locking = 0;
    cprintf("cpu with apicid %d: panic", cpu->apicid);
    cprintf(s);
    cprintf("\n");
    getcallerpcs(&s, pcs);
    for (i = 0;i < 10; i ++) {
        cprintf(" %p", pcs[i]);
    }
    panicked = 1; // 释放其他的CPU
    for (;;) {
        ;
    }
}
/**
 * @brief 将字符输入到cga的显示缓冲区
 * 
 * @param c 
 */

static void cgaputc(int c) {
    int pos;

    outb(CRTPORT, 14);
    pos = inb(CRTPORT + 1) << 8;

}

void consputc(int c) {
    if (panicked) {
        cli();
        for (;;) {
            ;
        }
    }

    if (c == BACKSPACE) {
        uartputc('\b');
        uartputc(' ');
        uartputc('\b');
    }
    else {
        uartputc(c); // 在串口回显字符
    }
    cgeputc(c); // 在cga回显字符
}

