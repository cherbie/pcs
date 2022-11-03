COMPILER = g++-12
CPP_FLAGS = -std=c++17 -Wall -Werror -pedantic

exe : solution.cpp
	$(COMPILER) $(CPP_FLAGS) -o exe solution.cpp


.phony : clean


clean :
	rm -rf exe *.o
