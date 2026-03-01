CC = gcc
CFLAGS = -Wall -Wextra -O3 -I./include
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/option_pricing.c
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/option_pricing.o
TARGET = $(BIN_DIR)/pricer

# Ensure the bin and obj directories exist
all: $(BIN_DIR) $(OBJ_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
