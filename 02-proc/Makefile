# Generic Makefile for compiling C programs
# Made by: Julien and Franck

CC = gcc # C compiler to use

# Define the source and include directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) # Define any compile-time flags
SRCS = $(wildcard $(SRC_DIR)/*.c) # source directory (where the .c files are)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS)) # list of all .c files in the SRC_DIR
BINS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRCS)) # list of all executables to build

# The all rule depends on the binaries and will be run if no arguments are given to make
all: $(BINS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Rule to link the object files into the binary
$(BIN_DIR)/%: $(BIN_DIR)/%.o
	$(CC) -o $@ $< $(CFLAGS)

# Rule to compile the source files into object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean # Tell make that clean is not a file name

# Rule to remove the object files and the binaries
clean:
	rm -rf $(BIN_DIR)

# Makefile syntax :
#  - -Iinclude : tell the compiler to look for header files in the include directory
#  - wildcard : returns a list of files matching a pattern
#  - patsubst : - returns a list of files with a pattern replaced by another pattern
#			    - function to generate a list of executable names from the list of source files.
#  - $< : first dependency (the .c file, the source file)
#  - $@ : target file (the executable)