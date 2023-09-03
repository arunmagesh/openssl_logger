CC = gcc
CFLAGS = -shared -o libssl_log.so -ldl -lssl -lcrypto
TARGET = libssl_log.so

.PHONY: all clean

all: $(TARGET)

$(TARGET): ssl_log.c
	$(CC) $(CFLAGS) ssl_log.c

clean:
	rm -f $(TARGET)
