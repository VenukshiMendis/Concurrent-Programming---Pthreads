# Define the compiler
CC = gcc

# Define the compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Define the linker flags
LDFLAGS = -lpthread

# Define the target executable
TARGET = main

# Define the source files
SRCS = main.c mutex.c read_write_lock.c serial.c random_numbers.c linked_list.c

# Define the object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link the object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	del $(OBJS) $(TARGET) results.csv file

.PHONY: all clean
