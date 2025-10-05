# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -g

# Source files
SRCS = src/main.c src/token.c src/variable.c src/tokenizer.c src/parser.c src/evaluator.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = build/calculator

# Create build directory if it doesn't exist
BUILD_DIR = build
$(shell mkdir -p $(BUILD_DIR))

# Default rule
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
