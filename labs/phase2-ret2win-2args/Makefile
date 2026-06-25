CC := gcc
CFLAGS := -Wall -Wextra -O0 -g -fno-stack-protector -no-pie -fno-pie
LDFLAGS := -Wl,-z,noexecstack

.PHONY: all clean checksec

all: ret2win_2args

ret2win_2args: ret2win_2args.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

checksec: ret2win_2args
	checksec ./ret2win_2args

clean:
	rm -f ret2win_2args
