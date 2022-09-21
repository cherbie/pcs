COMPILER = g++-12
CPP_FLAGS = --std=c++17 -Wall -Werror --pedantic
LINKER_FLAGS = 

exe : solution.cpp
	$(COMPILER) $(CPP_FLAGS) $(LINKER_FLAGS) solution.cpp -o exe

.phony: clean

clean :
	rm -f exe *.o

