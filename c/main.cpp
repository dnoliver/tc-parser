#include <stdio.h>
#include <stdlib.h>
#include "node.hpp"

extern int yyparse();
extern TranslationUnit* root;

int main(int argc, char **argv)
{
	int parse_result = yyparse();
	char *PARSE_AST = getenv ("PARSE_AST");
	char *PARSE_CODE = getenv ("PARSE_CODE");
	char *PARSE_SIMBOLS = getenv ("PARSE_SIMBOLS");
	
	if(parse_result == 0){
  		if (PARSE_AST != NULL){
			/** will print the ast in std string */
			std::cout << root->toStdString() << std::endl;	
		}
		
		if (PARSE_CODE != NULL){
			/** will print pretty code */
			std::cout << root->toPrettyCode() << std::endl;	
		}
		
		if(PARSE_SIMBOLS != NULL){
			SymbolTable *st = SymbolTable::Instance();
			std::cout << st->toStdString() << std::endl;
		}
	}
	
	return parse_result;
}