CC := gcc
CFLAGS := -Wall -Wextra -O0 -g -fno-stack-protector -no-pie -fno-pie
LDFLAGS := -Wl,-z,noexecstack

.PHONY: all clean checksec

all: ret2libc_leak

ret2libc_leak: ret2libc_leak.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

checksec: ret2libc_leak
	checksec ./ret2libc_leak

clean:
	rm -f ret2libc_leak
