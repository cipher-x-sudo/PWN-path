#include <stdio.h>
#include <unistd.h>

void __attribute__((naked)) gadget_pop_rdi(void) {
    __asm__("pop %rdi; ret");
}

void __attribute__((naked)) gadget_ret(void) {
    __asm__("ret");
}

static void vuln(void) {
    char buf[64];

    puts("Send your payload:");
    read(STDIN_FILENO, buf, 240);
    puts("Returning...");
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    puts("ret2libc leak lab");
    vuln();
    return 0;
}
