CC := gcc
CFLAGS := -Wall -Wextra -O0 -g -fno-stack-protector -no-pie -fno-pie
LDFLAGS := -Wl,-z,noexecstack

.PHONY: all clean checksec

all: ret2win_arg

ret2win_arg: ret2win_arg.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

checksec: ret2win_arg
	checksec ./ret2win_arg

clean:
	rm -f ret2win_arg
