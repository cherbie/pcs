CPP = g++-13
CPPFLAGS = -Wall -Werror -pedantic -g -D DEBUG

BUILD_DIR = build

run : solution.cpp
	mkdir -p $(BUILD_DIR)/
	$(CPP) $(CPPFLAGS) -o $(BUILD_DIR)/run solution.cpp

.phony: clean
clean :
	rm -rdf $(BUILD_DIR)
