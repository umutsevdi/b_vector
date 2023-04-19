SHELL := /bin/bash
CXXFLAGS = -Wall -Werror

# Files
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
INC = $(wildcard include/*.h)
BIN = bin/build

# Targets
all: $(BIN)

# Parameters:
# Depending on the test the compilation changes. - default 1
TEST ?= 1

$(BIN): $(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o $(BIN)

obj/%.o: src/%.c
# Replace the letter for the example
	@sed -i "s/#define TEST_./#define TEST_$(TEST)/" src/main.c
	gcc $(CXXFLAGS) -c $< -o $@  -Iinclude

clean:
	@sed -i "s/#define TEST_./#define TEST_1/" src/main.c
	rm -f $(OBJ) $(BIN)

# Example:
# make TEST=2
