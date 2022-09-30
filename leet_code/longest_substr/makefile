COMPILER = g++-12
CPPFLAGS = --std=c++17 -Wall -Werror -pedantic

exe : solution.cpp
	$(COMPILER) $(CPPFLAGS) -o exe solution.cpp

.phony : clean


clean : 
	rm -fd *.o exe
