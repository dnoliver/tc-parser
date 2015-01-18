#include <stdio.h>
#include "node.hpp"

extern int yyparse();
extern TranslationUnit* root;

int main(int argc, char **argv)
{
	int parse_result = yyparse();
	if(parse_result == 0){
		/** will print the ast in std string */
		std::cout << root->toStdString() << std::endl;
	}
	
	return parse_result;
}