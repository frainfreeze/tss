CXX=g++ 
CXXFLAGS=-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

all: docs build
	@echo '<html><head><meta http-equiv="refresh" content="0; url=./html/index.html" /></head><body></body></html>' > docs/index.html


build:
	$(CXX) -o tss main.cpp

docs:
	doxygen Doxyfile

clean:
	rm -f *.o
	rm -f tss

clean-docs:
	rm -rf docs

.PHONY: all build docs clean clean-docs