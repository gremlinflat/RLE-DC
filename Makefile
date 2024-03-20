
COMPILER = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++20 
ENTRYPOINT = main.cpp

BUILD_DIR = build

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
UTILS = $(wildcard $(SRC_DIR)/utils/*.cpp)

.PHONY: all build run clean re

build:
	@mkdir -p $(BUILD_DIR)
	$(COMPILER) $(CFLAGS) $(SRC) $(UTILS) $(ENTRYPOINT) -o $(BUILD_DIR)/main

run:
	@./$(BUILD_DIR)/main

clean:
	@rm -rf $(BUILD_DIR)

re: clean build

