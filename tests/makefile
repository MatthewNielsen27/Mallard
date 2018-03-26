CC=g++
CFLAGS=-I.

#All source files used by main test file
_SRC = duck.cpp
SRC= $(patsubst %,../src/%,$(_SRC))

#Name of main test file
MAIN = tests.cpp

tests: $(MAIN) $(SRC)
	g++ -o $@ $^ $(CFLAGS)
