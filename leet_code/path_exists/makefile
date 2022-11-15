COMPILER = g++-12
CPP_FLAGS = -Wall -Werror --std=c++17 -pedantic

exe : solution.cpp
	$(COMPILER) $(CPP_FLAGS) -o exe solution.cpp

.phony : clean


clean ::
	rm -rfd exe *.o
