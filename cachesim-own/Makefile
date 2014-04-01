all: cachesim ex1 ex2

cachesim: cachesim.cpp cachesim.h
	$(CXX) -Wall -g -o $@ cachesim.cpp

ex1: ex1.cpp cachesim.h
	$(CXX) -Wall -g -o $@ ex1.cpp

ex2: ex2.cpp cachesim.h
	$(CXX) -Wall -g -o $@ ex2.cpp

clean:
	rm -f cachesim ex1 ex2

