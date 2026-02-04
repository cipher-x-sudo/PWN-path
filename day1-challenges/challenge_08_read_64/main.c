/*
 * Challenge 08: read() overflow 64-bit.
 * Win: win()
 */
#include <stdio.h>
#include <unistd.h>

#define FLAG "flag{read_64_08}"

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
