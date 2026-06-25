CC := gcc
CFLAGS := -Wall -Wextra -O0 -g -fno-stack-protector -no-pie -fno-pie
LDFLAGS := -Wl,-z,noexecstack

.PHONY: all clean checksec

all: ret2win_3args

ret2win_3args: ret2win_3args.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

checksec: ret2win_3args
	checksec ./ret2win_3args

clean:
	rm -f ret2win_3args
