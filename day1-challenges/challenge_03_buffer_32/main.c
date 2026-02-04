/*
 * Challenge 03: buffer overflow 32-bit, read() no null terminator.
 * Win function: print_flag()
 */
#include <stdio.h>
#include <unistd.h>

#define FLAG "flag{buffer_32_03}"

void print_flag(void) {
	printf("Flag: %s\n", FLAG);
	fflush(stdout);
}

void vuln(void) {
	char buf[56];
	printf("Data: ");
	fflush(stdout);
	read(0, buf, 0x100);  /* no null; overflow */
	printf("Read done.\n");
}

int main(void) {
	vuln();
	return 0;
}
