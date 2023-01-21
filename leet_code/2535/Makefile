COMPILER = g++-12
CPPFLAGS = --std=c++20 -Wall -Werror -pedantic

exe : solution.cpp
	$(COMPILER) $(CPPFLAGS) -D=DEBUG -o exe solution.cpp

.PHONY : clean


clean : 
	rm -rfd exe *.o
