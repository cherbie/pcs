COMPILER = g++-12
CPPFLAGS = --std=c++17 -Wall -Werror --pedantic
LINKERFLAGS =

exe : solution.cpp
	$(COMPILER) $(CPPFLAGS) $(LINKERFLAGS) -o exe solution.cpp

.phony : clean

clean :
	rm -f exe *.o
