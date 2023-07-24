CPP = g++-13
CPPFLAGS = --std=c++17 -Wall -Werror -pedantic

BUILD_DIR = build

all : cppsolution

cppsolution : solution.cpp
	mkdir -p $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -o $(BUILD_DIR)/exe solution.cpp

cppsolution_RUN : cppsolution input.txt
	cat input.txt | $(BUILD_DIR)/exe

.phony : clean
clean :
	rm -rfd $(BUILD_DIR)
