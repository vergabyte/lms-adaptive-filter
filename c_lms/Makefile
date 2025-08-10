CC = gcc
CFLAGS = -O2 -Wall -Wextra -pedantic -std=c11
LDFLAGS = -lm

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SYNTHETIC = $(BIN_DIR)/lms_synthetic
FROMFILES = $(BIN_DIR)/lms_from_files

SYNTHETIC_SRC = $(SRC_DIR)/lms_synthetic.c
FROMFILES_SRC = $(SRC_DIR)/lms_from_files.c

.PHONY: all clean dirs

all: dirs $(SYNTHETIC) $(FROMFILES)

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) results

$(SYNTHETIC): $(SYNTHETIC_SRC)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(FROMFILES): $(FROMFILES_SRC)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) results/*
