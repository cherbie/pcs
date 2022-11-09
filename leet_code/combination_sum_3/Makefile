COMPILER=g++-12
CPPFLAGS=-Wacll -Werror -pedantic -std=c++17


exe: solution.cpp
	$(COMPILER) $(CPPFLAGS) -o exe solution.cpp


.phony : clean


clean:
	rm -rf exe *.o
