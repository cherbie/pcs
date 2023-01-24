COMPILER = g++-12
CPPFLAGS = -Wall --std=c++20 -pedantic

exe : solution.cpp 
	$(COMPILER) $(CPPFLAGS) -D=DEBUG solution.cpp -o exe

.PHONY : clean

test : exe input.txt
	cat input.txt | ./exe

clean : 
	rm -rfd *.o exe
