/*
 * Challenge 10: crackme style 64-bit.
 * gets() overflow; win function is reveal_flag().
 */
#define _GNU_SOURCE
#include <stdio.h>
extern char *gets(char *);

#define FLAG "flag{crackme_64_10}"

void reveal_flag(void) {
	printf("Revealed: %s\n", FLAG);
	fflush(stdout);
}

void vuln(void) {
	char buf[48];
	printf("Password: ");
	fflush(stdout);
	gets(buf);
	if (buf[0] == 'x')
		printf("Maybe try harder.\n");
}

int main(void) {
	vuln();
	return 0;
}
