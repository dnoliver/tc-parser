#!/bin/bash

echo "Parser Tests"
echo "============"
echo

function assert {
	echo $1
	(echo $1 | ./parser | grep "<.*>" | xmllint --format -) || exit 1
	#(echo $1 | ./parser ) || exit 1
	echo
}

## declarations and assignaments
assert "int x;"
assert "int x = 1;"
assert "int x = 1, y = 0;"
assert "float y;"
assert "float _x;"
assert "static;"
assert "static int;"
assert "extern static void;"
assert "int x; int i;"
assert "int *x;"
assert "int ***x;"
assert "int x[];"
assert "int x[5];"

## function definition
assert "int f(){}"
assert "int f(int x){}"
assert "int f(x){}"
assert "int f(){int x=0;}"

## ternary operator
assert "int a = 1?2:3;"

## binary operation
assert "int a = 1 + 2;"
assert "int a = 1 \* 2;"

## unary operation
assert "int a = a++;"
assert "int a = ++a;"

## jump statement
assert "int f(){ return; }"
assert "int f(){ break; }"
assert "int f(){ goto x; }"


echo
echo "Ok"
exit 0
