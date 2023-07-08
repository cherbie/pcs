CC = gcc-13
CFLAGS += -Wall -Werror -pedantic -g

BUILD_DIR = build/

all : csolution

# C solution
runc : csolution
	cat input.txt | $(BUILD_DIR)run
csolution : solution.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)run solution.c

.phony: clean
clean:
	rm -rdf $(BUILD_DIR)

