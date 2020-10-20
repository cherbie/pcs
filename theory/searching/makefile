GCC=g++-10 --std=c++11 -Wall -Werror -pedantic

all : binary_search

binary_search.o : binary_search.cpp
	$(GCC) -c binary_search.cpp

binary_search : binary_search.o
	$(GCC) -o binary binary_search.o

clean:
	rm -rfv *.o
