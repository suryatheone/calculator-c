# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -g
LDFLAGS = -lcunit -lm

# Directories
BIN_DIR = build/bin
OBJ_DIR = build/obj
TEST_DIR = tests

# Source files for the main application (excluding main.c)
SRCS = $(filter-out src/main.c, $(wildcard src/*.c))

# Object files
OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Test source files and their corresponding executables
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_SRCS))

# Executable name
TARGET = $(BIN_DIR)/calculator

# Create necessary directories
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

# Default rule
all: $(TARGET)

# Linking rule
$(TARGET): src/main.c $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lm

# Compilation rule
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build and run all tests
test: $(TEST_BINS)
	@echo "Running tests..."
	@for test_bin in $(TEST_BINS); do \
		echo "=> Running $$test_bin"; \
		./$$test_bin; \
	done
	@echo "All tests passed."

# Rule to build individual test executables
$(BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(OBJS) $(LDFLAGS)

# Clean rule
clean:
	rm -rf build

.PHONY: all clean test
