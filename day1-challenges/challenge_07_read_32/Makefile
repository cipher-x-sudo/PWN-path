CC = gcc
CFLAGS = -m32 -fno-stack-protector -no-pie -O0 -z noexecstack -Wno-stringop-overflow
TARGET = vuln

.PHONY: all clean

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)
