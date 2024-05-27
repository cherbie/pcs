GCC := g++-13
CPPFLAGS := --std=c++17 -Wall -Werror -pedantic

BUILD_DIR := build

app : solution.cpp 
	mkdir -p $(BUILD_DIR)
	$(GCC) $(CPPFLAGS) -DDEBUG -o $(BUILD_DIR)/app solution.cpp

.PHONY : clean

clean :
	rm -rdf build
