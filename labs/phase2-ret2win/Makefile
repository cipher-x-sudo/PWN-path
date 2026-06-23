CC := gcc
CFLAGS := -Wall -Wextra -O0 -g -fno-stack-protector -no-pie -fno-pie
LDFLAGS := -Wl,-z,noexecstack

.PHONY: all clean checksec

all: ret2win

ret2win: ret2win.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

checksec: ret2win
	checksec ./ret2win

clean:
	rm -f ret2win

