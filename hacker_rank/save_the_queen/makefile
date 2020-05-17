GPP=g++-9 -std=c++11 -Wall -Werror -pedantic

app : soln.o test
	$(GPP) -o app soln.o

test : test.o
	$(GPP) -o test test.o

soln.o : soln.cpp
	$(GPP) -c -o soln.o soln.cpp 

test.o : run.cpp 
	$(GPP) -c -o test.o run.cpp

clear :
	rm -r *.o