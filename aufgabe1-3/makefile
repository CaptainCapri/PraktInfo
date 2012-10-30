all: aufgabe1_1

aufgabe1_1: ./ue1/main.cpp
	$(CXX) -Wall -g -o $@ ./ue1/main.cpp ./ue1/Number.cpp

test: aufgabe1_1
	./aufgabe1_1

clean: 
	rm -f aufgabe1_1
