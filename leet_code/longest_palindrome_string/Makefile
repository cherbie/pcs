COMPILER = g++-12
CPPFLAGS = -Wall -Werror -pedantic --std=c++20

exe : solution.cpp
	$(COMPILER) $(CPPFLAGS) -o exe solution.cpp

.phony : clean
	rm -drf exe *.o
