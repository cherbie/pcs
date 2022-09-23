COMPILER = g++-11
CPPFLAGS = --std=c++17 -Wall -Werror --pedantic
LINKER_FLAGS =

exe : solution.cpp
	$(COMPILER) $(CPPFLAGS) $(LINKER_FLAGS) -o exe solution.cpp

.phony : clean


clean :
	rm -f *.o exe
