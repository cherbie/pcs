CC = gcc-13 -x c
CFLAGS = -std=c99 -Wall -Werror -pedantic -g -D DEBUG

BUILD_DIR = build

run : solution
	./build/run

solution : solution.c
	mkdir -p $(BUILD_DIR)/
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/run solution.c

debug : solution
	lldb $(BUILD_DIR)/run

.phony: clean
clean :
	rm -rdf $(BUILD_DIR)
