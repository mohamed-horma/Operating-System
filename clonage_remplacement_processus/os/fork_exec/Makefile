# Compiler
CC = gcc

# Compiler and linker flags
CPPFLAGS = -Iinclude
CFLAGS   = -Wall -Wextra -pedantic -g
LDFLAGS  =

# Directories
SRC_DIR   = src
BIN_DIR   = bin
OBJ_DIR   = obj

# Targets
TARGETS   = very_simple simple iplot four

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

VERY_SIMPLE_OBJ = $(OBJ_DIR)/very_simple/main.o $(OBJ_DIR)/logger.o
SIMPLE_OBJ      = $(OBJ_DIR)/simple/main.o      $(OBJ_DIR)/logger.o
IPLOT_OBJ       = $(OBJ_DIR)/iplot/main.o       $(OBJ_DIR)/iplot/iplot.o $(OBJ_DIR)/logger.o
FOUR_OBJ        = $(OBJ_DIR)/four/main.o        $(OBJ_DIR)/four/four.o $(OBJ_DIR)/logger.o

# Phony targets
.PHONY: all clean

all: $(TARGETS)

very_simple: $(VERY_SIMPLE_OBJ)
	@test -d "$(BIN_DIR)" || mkdir -p "$(BIN_DIR)"
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

simple: $(SIMPLE_OBJ)
	@test -d "$(BIN_DIR)" || mkdir -p "$(BIN_DIR)"
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

iplot: $(IPLOT_OBJ)
	@test -d "$(BIN_DIR)" || mkdir -p "$(BIN_DIR)"
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

four: $(FOUR_OBJ)
	@test -d "$(BIN_DIR)" || mkdir -p "$(BIN_DIR)"
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@test -d "$(dir $@)" || mkdir -p "$(dir $@)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@test ! -f commands.gp || rm -f commands.gp
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
