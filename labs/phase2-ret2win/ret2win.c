#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void win(void) {
    puts("local{ret2win_control_flow}");
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

