CC := gcc
CFLAGS := -Wall -Wextra -O0 -g -fno-stack-protector -no-pie -fno-pie
LDFLAGS := -Wl,-z,noexecstack

.PHONY: all clean checksec

all: cyclic_offset

cyclic_offset: cyclic_offset.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

checksec: cyclic_offset
	checksec ./cyclic_offset

clean:
	rm -f cyclic_offset
