#!/bin/bash

echo "Parser Tests"
echo "============"
echo

function assert {
	(echo $1 | PARSE_CODE=TRUE ./parser ) || exit 1
	echo
	(echo $1 | PARSE_AST=TRUE ./parser | grep "<.*>" | xmllint --format -) || exit 1
	echo
	#(echo $1 | PARSE_SIMBOLS=TRUE ./parser | grep "<.*>" | xmllint --format -) || exit 1
	#echo
	(echo $1 | GENERATE_CODE=TRUE ./parser ) || exit 1
	echo
}

function assertFile {
	(cat $1 | PARSE_CODE=TRUE ./parser ) || exit 1
	echo
	(cat $1 | PARSE_AST=TRUE ./parser | grep "<.*>" | xmllint --format -) || exit 1
	echo
	#(cat $1 | PARSE_SIMBOLS=TRUE ./parser | grep "<.*>" | xmllint --format -) || exit 1
	#echo
	(cat $1 | GENERATE_CODE=TRUE ./parser ) || exit 1
	echo
}


## type declaration
assert "static;"
assert "static int;"
assert "extern static void;"

## declarations
assert "int x;"
assert "float y;"
assert "float _x;"
assert "int x; int i;"
assert "int *x;"
assert "int **x;"
assert "int x[];"
assert "int x[5];"

## assignament
assert "int x = 1;"
assert "int x = 1, y = 0;"
assert "int a = (1+1);"

## ternary operator
assert "int a = 1?2:3;"
assert "int a = 1==1?2:3;"

## binary operation
assert "int a = 1 + 2;"
assert "int a = 1 \* 2;"
assert "int a = 1 \* 2 + 1 \* 3 - 5;"

## logical operation
assert "int a = 4 > 20;"
assert "int x=1<10 && 10==10;";

## unary operation
assert "int x = 0; int a = x++;"
assert "int x = 0; int a = ++x;"

## function definition
assert "int f(){}"
assert "int f(int x){}"
assert "int f(int x,int y){}"
assert "int f(int x,int y,int z){}"
assert "int f(){int x=0;}"
assert "int f(){int x=0; g(x); }"

## SelectionStatement
assert "int f(){ if(1){ return; }}"
assert "int f(){ if(1){ return a; } else { return b;}}"
assert "int f(){ switch(1){ return; }}"

##IterationStatement
assert "int f(){ while(1) { return;}}"
assert "int f(){ do {int i;} while(1);}"
assert "int f(){ int i; for(i=0; i!=2;) {return;}}"
assert "int f(){ int i; for(i=0; i!=2; i++) {return;}}"

## jump statement
assert "int f(){ return; }"
assert "int f(){ break; }"
assert "int f(){ goto x; x: return 0;}"
assert "int f(){ return 1+1; }"

## complex programs 
assertFile "tests/factorial.c"
assertFile "tests/simple.c"

echo
echo "Ok"
exit 0
