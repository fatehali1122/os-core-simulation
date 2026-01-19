# 1. Compiler setup
CC = gcc
CFLAGS = -Wall -Wextra -I./src -I./include

SRCS = src/filesystem/file_system.c \
       src/interrupt/interrupt.c \
       src/memory/memory_manager.c \
       src/process/process_scheduler.c \
       src/syscall/syscall.c \
       src/main.c

TARGET = os_simulation

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)