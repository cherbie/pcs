CC = g++-11
CCFLAGS = -std=c++17 -Wall -Werror -pedantic -g3

BINDIR := ./bin
SRC := main.cpp
OBJDIR := ./obj
OBJ := $(OBJDIR)/main.o

all : $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) $(CCFLAGS) $(OBJ) -o $(BINDIR)/run

$(OBJDIR)/%.o : %.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CCFLAGS) -c -o $@ $^

.phony : clean

clean :
	rm -rdf $(BINDIR) $(OBJDIR)