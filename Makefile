TARGET = linear

CC = clang
CFLAGS = -Wall -Wextra -std=c11 -g

SRC = main.c model.c
HEADERS = model.h

all: build run

build:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run:
	@echo "\n--- Running Program ---"
	./$(TARGET)

clean:
	rm -f $(TARGET)
