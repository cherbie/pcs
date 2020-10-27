GCC=g++-10 --std=c++11 -Wall -Werror -pedantic

all: linked_list

linked_list: linked_list.o
	$(GCC) -o linked_list linked_list.o 

linked_list.o: linked_list.cpp linked_list.h
	$(GCC) -c linked_list.cpp linked_list.h

clean:
	rm -rfv *.o *.h.gch
