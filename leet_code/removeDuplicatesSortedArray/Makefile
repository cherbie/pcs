CPP = g++-13
CC = gcc-13
CPPFLAGS = --std=c++17 -Wall -Werror -pedantic
CFLAGS = --std=c99 -Wall -Werror -pedantic

BUILD_DIR = build

all : csolution

csolution : solution.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/exe solution.c

cppsolution : solution.cpp
	mkdir -p $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -o $(BUILD_DIR)/exe solution.cpp

cppsolution_RUN : cppsolution input.txt
	cat input.txt | $(BUILD_DIR)/exe

csolution_RUN : csolution input.txt
	cat input.txt | $(BUILD_DIR)/exe

.phony : clean
clean :
	rm -rfd $(BUILD_DIR)
