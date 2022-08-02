
#include <stdio.h>

void cprintf(char *fmt, ...) {
    printf("fmt: %s\n", fmt);
    unsigned int *argp;
    char *s;

    argp = (unsigned int *)(void *)(&fmt + 1);

    printf("argp1: %d\n", *argp ++);
    printf("argp2: %d\n", *argp ++);
}

int main(int argc, const char **argv) {
    cprintf("cpu with apicid %d: panic", 3);
    return 0;
}