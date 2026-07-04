CC := gcc
CFLAGS := -Wall -Wextra -O0 -g -msse2 -mno-stackrealign -fno-stack-protector -no-pie -fno-pie
LDFLAGS := -Wl,-z,noexecstack

.PHONY: all clean checksec

all: stack_alignment_sse

stack_alignment_sse: stack_alignment_sse.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

checksec: stack_alignment_sse
	checksec ./stack_alignment_sse

clean:
	rm -f stack_alignment_sse
