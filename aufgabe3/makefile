all: skiplist codegen

skiplist: ./ue03/main.cpp
	$(CXX) -Wall -g -o $@ ./ue03/main.cpp

codegen: codegen.cpp
	g++ -o codegen codegen.cpp
	./codegen > calc_expr.s
	as -c -o calc_expr.o calc_expr.s
	g++ -c -o codelink.o codelink.cpp
	g++ -o calc codelink.o calc_expr.o


test: codegen skiplist
	./calc
	./skiplist

valgrind: codegen skiplist
	valgrind --leak-check=full ./calc
	valgrind --leak-check=full ./skiplist

clean: 
	rm -f skiplist
	rm -f codegen.o
	rm -f codegen
	rm -f calc_expr.s
	rm -f calc_expr.o
	rm -f calc
	rm -f codelink.o
