#!/bin/bash

echo "Parser Tests"
echo "============"
echo

function assert {
	(echo $1 | PARSE_CODE=TRUE ./parser ) || exit 1
	echo
	(echo $1 | PARSE_AST=TRUE ./parser | grep "<.*>" | xmllint --format -) || exit 1
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

## binary operation
assert "int a = 1 + 2;"
assert "int a = 1 \* 2;"

## unary operation
assert "int a = a++;"
assert "int a = ++a;"

## function definition
assert "int f(){}"
assert "int f(int x){}"
assert "int f(int x,int y){}"
assert "int f(int x,int y,int z){}"
assert "int f(){int x=0;}"

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
assert "int f(){ goto x; }"
assert "int f(){ return 1+1; }"

## complex programs 
assert "int main(int argc,char **argv){ int x; int z[1]; x = 1; x++; return; }"
assert "int main(){ f(); }"
assert "int main(){ f(1); }"
assert "int main(){ int x[5]; x[1]++; }"

echo
echo "Ok"
exit 0
