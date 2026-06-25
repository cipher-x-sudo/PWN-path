#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct request {
    char label[11];
    char input[73];
    unsigned int marker;
};

static void win(void) {
    puts("local{cyclic_offset_found}");
    fflush(stdout);
    exit(0);
}

static void vuln(void) {
    struct request req = {0};

    puts("Send your cyclic pattern:");
    read(STDIN_FILENO, req.input, 220);
    puts("Returning...");
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    vuln();
    return 0;
}
