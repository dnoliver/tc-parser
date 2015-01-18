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

echo
echo "Ok"
exit 0
