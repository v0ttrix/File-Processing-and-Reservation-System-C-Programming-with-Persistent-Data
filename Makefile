# Makefile for File Processing and Reservation System
# Author: Jaden Mardini

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -O2 -g
CPPFLAGS = -Iinclude
LDFLAGS = 
LDLIBS = 

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
OBJ_DIR = obj
TEST_DIR = tests

# Source files
FILE_CONVERTER_SRC = $(SRC_DIR)/file_converter/file_converter.c
RESERVATION_SYSTEM_SRC = $(SRC_DIR)/reservation_system/reservation_system.c
RESERVATION_MAIN_SRC = $(SRC_DIR)/reservation_system/main.c

# Object files
FILE_CONVERTER_OBJ = $(OBJ_DIR)/file_converter.o
RESERVATION_SYSTEM_OBJ = $(OBJ_DIR)/reservation_system.o
RESERVATION_MAIN_OBJ = $(OBJ_DIR)/reservation_main.o

# Executables
FILE_CONVERTER_EXEC = $(BIN_DIR)/file_converter
RESERVATION_EXEC = $(BIN_DIR)/reservation_system

.PHONY: all clean directories file_converter reservation_system test help

# Default target
all: directories $(FILE_CONVERTER_EXEC) $(RESERVATION_EXEC)

# Create directories
directories:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR) $(TEST_DIR)

# File converter executable
$(FILE_CONVERTER_EXEC): $(FILE_CONVERTER_OBJ)
	@echo "Linking file converter..."
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "Built: $@"

# Reservation system executable
$(RESERVATION_EXEC): $(RESERVATION_SYSTEM_OBJ) $(RESERVATION_MAIN_OBJ)
	@echo "Linking reservation system..."
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "Built: $@"

# Object file rules
$(OBJ_DIR)/file_converter.o: $(FILE_CONVERTER_SRC)
	@echo "Compiling file_converter.c..."
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/reservation_system.o: $(RESERVATION_SYSTEM_SRC) $(INCLUDE_DIR)/reservation_system.h
	@echo "Compiling reservation_system.c..."
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/reservation_main.o: $(RESERVATION_MAIN_SRC) $(INCLUDE_DIR)/reservation_system.h
	@echo "Compiling reservation main.c..."
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Individual targets
file_converter: directories $(FILE_CONVERTER_EXEC)

reservation_system: directories $(RESERVATION_EXEC)

# Test target
test: all
	@echo "Running file converter test..."
	@echo "Hello World Test" > test_input.txt
	@$(FILE_CONVERTER_EXEC) test_input.txt test_output.txt
	@echo "File converter test completed"
	@rm -f test_input.txt test_output.txt

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	rm -f test_input.txt test_output.txt reservations.dat
	@echo "Clean complete"

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build all executables (default)"
	@echo "  file_converter   - Build file converter only"
	@echo "  reservation_system - Build reservation system only"
	@echo "  test            - Run basic functionality tests"
	@echo "  clean           - Remove build artifacts"
	@echo "  help            - Show this help message"
