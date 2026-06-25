#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void __attribute__((naked)) gadget_rdi(void) {
    __asm__("pop %rdi; ret");
}

void __attribute__((naked)) gadget_rsi(void) {
    __asm__("pop %rsi; ret");
}

void __attribute__((naked)) gadget_rdx(void) {
    __asm__("pop %rdx; ret");
}

static void win(unsigned long key1, unsigned long key2, unsigned long key3) {
    if (key1 != 0xdeadbeefUL) {
        puts("wrong first key");
        exit(1);
    }

    if (key2 != 0xcafebabeUL) {
        puts("wrong second key");
        exit(1);
    }

    if (key3 != 0x13371337UL) {
        puts("wrong third key");
        exit(1);
    }

    puts("local{ret2win_three_argument_control}");
    fflush(stdout);
    exit(0);
}

static void vuln(void) {
    char buf[64];

    puts("Send your payload:");
    read(STDIN_FILENO, buf, 200);
    puts("Returning...");
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    vuln();
    return 0;
}
