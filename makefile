CXX=g++ 
CXXFLAGS=-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

all: docs build

build:
	$(CXX) -o main-out main.cpp

docs:
	doxygen Doxyfile

clean:
	rm -f *.o
	rm -f main-out

clean-docs:
	rm -rf docs

.PHONY: all build docs clean clean-docs