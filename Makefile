CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.c)

TARGET = forkshell

all:
$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
./$(TARGET)

clean:
rm -f $(TARGET)

rebuild: clean all

.PHONY: all run clean rebuild
