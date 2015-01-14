all: parser
	
parser: lex.yy.cpp ansi-c.tab.cpp main.cpp 
	g++ $^ -o $@

lex.yy.cpp: ansi-c.l
	lex  -o $@ $^

ansi-c.tab.cpp: ansi-c.y
	bison -d $^ -o $@

ansi-c.tab.hpp: ansi-c.tab.cpp

test: parser
	./test.sh

clean:
	rm -f ansi-c.tab.cpp ansi-c.tab.hpp lex.yy.cpp parser 