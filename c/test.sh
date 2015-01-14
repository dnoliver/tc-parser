#!/bin/bash

echo "Parser Tests"
echo "============"
echo

function assert {
	(echo $1 | ./parser) || exit 1
}

assert "int x;"
assert "int x = 1;"
assert "int x = 1, y = 0;"
assert "float y;"
assert "float _x;"

assert "void f(){}"
assert "int f(int a, int b){}"
assert "void main(int argc, char** argc){ return 0; }"
assert "double f(){ int x = 1; return 0; }"

assert "void main(){ if(1){return 0;} }"
assert "void main(){ int i,x=0; for(i=0;i<1;i++){  x++; } }"

echo
echo "Ok"
exit 0