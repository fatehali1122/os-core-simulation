ifeq ($(OS),Windows_NT)
	
	RM = del
	TARGET = os_simulation.exe
	
else 

	RM = rm -f
	TARGET = os_simulation
	
endif

# Compiler setup
CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRCS = src/filesystem/file_system.c \
       src/interrupt/interrupt.c \
       src/memory/memory_manager.c \
       src/process/process_scheduler.c \
	   src/process/process.c \
       src/syscall/syscall.c \
       src/main.c


all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	$(RM) $(TARGET)