#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <xmmintrin.h>

__attribute__((noinline)) static void prepare_reward(void) {
    __m128 values = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);
    float result[4] __attribute__((aligned(16)));

    _mm_store_ps(result, values);
    printf("Verification: %.0f\n", result[0]);
}

__attribute__((noinline)) static void win(void) {
    prepare_reward();
    puts("local{real_stack_alignment}");
    exit(0);
}

__attribute__((noinline)) static void vuln(void) {
    char buffer[64];

    puts("Enter payload:");
    read(STDIN_FILENO, buffer, 200);
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    vuln();
    return 0;
}
