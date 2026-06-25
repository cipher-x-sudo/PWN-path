#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void __attribute__((naked)) gadget(void) {
    __asm__("pop %rdi; ret");
}

static void win(unsigned long key) {
    if (key != 0xdeadbeefUL) {
        puts("wrong key");
        exit(1);
    }

    puts("local{ret2win_argument_control}");
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
