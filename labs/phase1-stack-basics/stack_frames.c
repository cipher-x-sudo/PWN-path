#include <stdint.h>
#include <stdio.h>

static long inspect_me(long a, long b, long c) {
    volatile long local_a = a + 1;
    volatile long local_b = b + 2;
    volatile long local_c = c + 3;
    volatile long total = local_a + local_b + local_c;

    printf("local_a=%ld local_b=%ld local_c=%ld total=%ld\n",
           local_a, local_b, local_c, total);
    return total;
}

int main(void) {
    uint64_t marker = 0x4142434445464748ULL;
    printf("marker is at %p and has value 0x%lx\n", (void *)&marker, marker);
    long result = inspect_me(10, 20, 30);
    printf("result=%ld\n", result);
    return 0;
}

