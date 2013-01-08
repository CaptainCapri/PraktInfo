all: uebung5

uebung5: 
	$(CXX) -Wall -g -o $@ main.cpp -std=c++0x

test: uebung5
	./uebung5

valgrind: uebung5
	valgrind ./uebung5

valgrind-deep: uebung5
	valgrind --leak-check=full ./uebung5

clean: 
	rm -f uebung5