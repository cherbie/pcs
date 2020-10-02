GCC=g++-10 -std=c++11 -m64 -Wall -Werror -pedantic

all: bubble merge quick

bubble: bubble_sort.o
	$(GCC) -o bubble_sort bubble_sort.o

merge: merge_sort.o
	$(GCC) -o merge_sort merge_sort.o

quick: quick_sort.o
	$(GCC) -o quick_sort quick_sort.o

quick_sort.o: quick_sort.cpp
	$(GCC) -c quick_sort.cpp

bubble_sort.o: bubble_sort.cpp
	$(GCC) -c bubble_sort.cpp

merge_sort.o: merge_sort.cpp
	$(GCC) -c merge_sort.cpp

clean:
	rm -rv *.o
