/*
 * Challenge 05: gets() overflow 32-bit, different buffer size.
 * Win: get_flag()
 */
#define _GNU_SOURCE
#include <stdio.h>
extern char *gets(char *);

#define FLAG "flag{gets_32_05}"

void get_flag(void) {
	printf("Here: %s\n", FLAG);
	fflush(stdout);
}

void vuln(void) {
	char buf[64];
	printf("Say something: ");
	fflush(stdout);
	gets(buf);
}

int main(void) {
	vuln();
	return 0;
}
