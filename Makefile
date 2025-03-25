
TARGET = linear

CC = clang
CFLAGS = -Wall -Wextra -std=c11 -g -fsanitize=address -fno-omit-frame-pointer

SRC = main.c model.c
HEADERS = model.h

all: build run

build:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run:
	@echo "\n--- Running Program with AddressSanitizer ---"
	./$(TARGET)

clean:
	rm -f $(TARGET)
