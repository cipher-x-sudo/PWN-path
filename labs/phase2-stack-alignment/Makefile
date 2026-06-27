CC := gcc
CFLAGS := -Wall -Wextra -O0 -g -fno-stack-protector -no-pie -fno-pie
LDFLAGS := -Wl,-z,noexecstack

.PHONY: all clean checksec

all: stack_alignment

stack_alignment: stack_alignment.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

checksec: stack_alignment
	checksec ./stack_alignment

clean:
	rm -f stack_alignment
