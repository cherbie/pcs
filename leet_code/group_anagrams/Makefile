CPP = g++-13
C = gcc-13
CPPFLAGS = --std=c++20 -Wall -Werror -pedantic
CFLAGS = --std=c17 -Werror -Wpedantic

exe : solution.cpp
	$(CPP) $(CPPFLAGS) -D=DEBUG -o exe solution.cpp

exe-c: solution.c
	$(C) $(CFLAGS) -D=DEBUG -o exe solution.c

.PHONY : clean

run : exe
	./exe

run-py : solution.py
	cat input.txt | python3 solution.py

clean : 
	rm -rfd exe *.o
