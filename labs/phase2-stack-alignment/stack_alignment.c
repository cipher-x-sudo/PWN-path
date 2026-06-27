#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

__attribute__((naked, noinline)) static void alignment_check(void) {
    __asm__(
        "push %rbp\n"
        "mov %rsp, %rbp\n"
        "sub $0x10, %rsp\n"
        "pxor %xmm0, %xmm0\n"
        "movaps %xmm0, (%rsp)\n"
        "leave\n"
        "ret\n");
}

static void win(void) {
    alignment_check();
    puts("local{stack_alignment_fixed}");
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
