/*
 * Challenge 02: ret2win (64-bit)
 * Overflow with gets(), redirect to win().
 * Compile: no PIE, no canary.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
extern char *gets(char *);

#define FLAG "flag{ret2win_64_02}"

void win(void) {
	printf("You win! %s\n", FLAG);
	fflush(stdout);
}

void vuln(void) {
	char buf[40];
	printf("Input: ");
	fflush(stdout);
	gets(buf);
	printf("You said: %s\n", buf);
}

int main(void) {
	vuln();
	return 0;
}
