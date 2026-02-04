CC = gcc
CFLAGS = -fno-stack-protector -no-pie -O0 -z noexecstack -Wno-deprecated-declarations
TARGET = vuln

.PHONY: all clean

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)
