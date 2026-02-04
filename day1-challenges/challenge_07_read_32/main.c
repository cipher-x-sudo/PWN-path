/*
 * Challenge 07: read() overflow 32-bit, larger read size.
 * Win: win()
 */
#include <stdio.h>
#include <unistd.h>

#define FLAG "flag{read_32_07}"

void win(void) {
	printf("Win: %s\n", FLAG);
	fflush(stdout);
}

void vuln(void) {
	char buf[72];
	printf("Enter up to 512 bytes: ");
	fflush(stdout);
	read(0, buf, 0x200);
}

int main(void) {
	vuln();
	return 0;
}
