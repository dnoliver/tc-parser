#!/bin/bash

echo "Parser Tests"
echo "============"
echo

function assert {
	(echo $1 | ./parser) || exit 1
}

# declarations and assignaments
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
assert "int a = (1+1);"

# function definition
assert "int f(){}"
assert "int f(int x){}"
assert "int f(x){}"
assert "int f(){int x=0;}"

echo
echo "Ok"
exit 0
