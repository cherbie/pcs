CPP = g++-13
CPPFLAGS = --std=c++17 -Wall -Werror -pedantic

BUILD_DIR = build

exe : cppsolution

cppsolution : solution.cpp
	mkdir -p $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -o $(BUILD_DIR)/exe solution.cpp

cppsolution_RUN : cppsolution
	cat input.txt | $(BUILD_DIR)/exe

.phony : clean
clean : 
	rm -fdr $(BUILD_DIR)
