CXX = g++ -Wall -g

all: codelink compiler

calc_expr.s: codegen
	./codegen > calc_expr.s

codelink: codelink.cpp calc_expr.s
	$(CXX) -o $@ codelink.cpp calc_expr.s

test: codelink
	./codelink

compiler: compiler.cpp
	$(CXX) -o $@ compiler.cpp

clean:
	rm -f codegen codelink calc_expr.s compiler
