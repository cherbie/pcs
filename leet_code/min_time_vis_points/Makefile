COMPILER = g++-12
CPPFLAGS = -Werror -std=c++20 -pedantic

exe : solution.cpp
	$(COMPILER) $(CPPFLAGS) -o exe solution.cpp

.phony : clean


clean :
	rm -rf exe *.o
