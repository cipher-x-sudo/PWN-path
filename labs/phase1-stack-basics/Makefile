CC := gcc
CFLAGS := -Wall -Wextra -O0 -g -fno-omit-frame-pointer

.PHONY: all clean

all: stack_frames

stack_frames: stack_frames.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f stack_frames

