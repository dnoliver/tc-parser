all: parser

clean:
	rm ./src/parser.cpp ./src/parser.hpp parser ./src/tokens.cpp

./src/parser.cpp: ./src/parser.y
	bison -d -o $@ $^
	
./src/parser.hpp: ./src/parser.cpp

./src/tokens.cpp: ./src/tokens.l ./src/parser.hpp
	lex -o $@ $^

parser: ./src/parser.cpp ./src/codegen.cpp ./src/main.cpp ./src/tokens.cpp
	g++ -o $@ ./src/*.cpp
