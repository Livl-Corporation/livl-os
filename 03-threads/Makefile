# Generic Makefile for compiling C programs
# Made by: Julien and Franck

# Define some colors for the output
BLUE=\033[0;34m
GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m # No Color
BOLD=\033[1m
PURPLE=\033[0;35m

CC = gcc # C compiler to use

# Define the source and include directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
DIR_NAME = $(notdir $(shell pwd)) # Get the current directory name

CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -lpthread # Define any compile-time flags
SRCS = $(wildcard $(SRC_DIR)/*.c) # source directory (where the .c files are)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS)) # list of all .c files in the SRC_DIR
BINS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRCS)) # list of all executables to build

# The all rule depends on the binaries and will be run if no arguments are given to make
all: print_dir_name $(BINS)
	@if [ -d "$(BIN_DIR)" ]; then \
			echo "$(GREEN)$(BOLD)All executables are up-to-date in $(BIN_DIR)$(NC)"; \
	fi

# Print the directory name in blue
print_dir_name:
	@echo "$(PURPLE)$(BOLD)***** Makefile - $(DIR_NAME)*****$(NC)\n"

$(BIN_DIR):
	@echo "${BLUE}$(BOLD)Creation of the bin directory:${NC}"
	@printf " → "
	mkdir -p $(BIN_DIR)
	@echo " → ${GREEN}Directory created: $(BIN_DIR)${NC}\n"

# Rule to link the object files into the binary
$(BIN_DIR)/%: $(BIN_DIR)/%.o | $(BIN_DIR)
	@printf " → "
	$(CC) -o $@ $< $(CFLAGS)
	@echo " → ${GREEN}Run the executable: ./$@${NC}\n"
	

# Rule to compile the source files into object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	@echo "${BLUE}$(BOLD)Compilation of $<:${NC}"
	@printf " → "
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean # Tell make that clean is not a file name

# Rule to remove the object files and the binaries
clean:
	@echo "$(PURPLE)$(BOLD)***** Makefile - $(DIR_NAME)*****$(NC)\n"
	@echo "${RED}$(BOLD)Deletion of the bin folder:${NC}"
	@printf " → "
	rm -rf $(BIN_DIR)

# Makefile syntax :
#  - -Iinclude : tell the compiler to look for header files in the include directory
#  - wildcard : returns a list of files matching a pattern
#  - patsubst : - returns a list of files with a pattern replaced by another pattern
#			    - function to generate a list of executable names from the list of source files.
#  - $< : first dependency (the .c file, the source file)
#  - $@ : target file (the executable)
#  - | $(BIN_DIR) : $(BIN_DIR) must be built before the other targets, but it doesn’t need to be rebuilt every time the other targets are built, only if it doesn’t exist 