CPP = g++-13
CPPFLAGS = --std=c++20 -Wall -Werror -pedantic -g -D DEBUG

BUILD_DIR = build

all : cppsolution

cppsolution : solution.cpp
	mkdir -p $(BUILD_DIR)/
	$(CPP) $(CPPFLAGS) -o $(BUILD_DIR)/cppsolution solution.cpp

cppsolution_RUN : cppsolution
	cat input.txt | ./$(BUILD_DIR)/cppsolution

cppsolution_DEBUG : cppsolution
	lldb $(BUILD_DIR)/cppsolution

.phony: clean
clean :
	rm -rdf $(BUILD_DIR)
