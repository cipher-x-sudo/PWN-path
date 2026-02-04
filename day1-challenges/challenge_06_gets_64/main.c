/*
 * Challenge 06: gets() overflow 64-bit.
 * Win: get_flag()
 */
#define _GNU_SOURCE
#include <stdio.h>
extern char *gets(char *);

#define FLAG "flag{gets_64_06}"

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
