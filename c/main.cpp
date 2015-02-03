#include <stdio.h>
#include <stdlib.h>
#include "node.hpp"
#include "CodeGen.hpp"
#include "CodeString.hpp"

/*
 *  _______________________________________
 * / Q: How many IBM CPU's does it take to \
 * | do a logical right shift? A: 33. 1 to |
 * | hold the bits and 32 to push the      |
 * \ register.                             /
 *  ---------------------------------------
 *         \   ^__^
 *          \  (oo)\_______
 *             (__)\       )\/\
 *                 ||----w |
 *                 ||     ||
 */

extern int yyparse();
extern TranslationUnit* root;

int main(int argc, char **argv)
{
	int parse_result = yyparse();
	char *PARSE_AST = getenv ("PARSE_AST");
	char *PARSE_CODE = getenv ("PARSE_CODE");
	char *PARSE_SIMBOLS = getenv ("PARSE_SIMBOLS");
	char *GENERATE_CODE = getenv ("GENERATE_CODE");
	
	std::cout << std::endl;
	
	if(parse_result == 0){
  		if (PARSE_AST != NULL){
			/** will print the ast in std string */
			std::cout << std::endl;
			std::cout << root->toStdString() << std::endl;	
		}
		
		if (PARSE_CODE != NULL){
			/** will print pretty code */
			CodeBlock *context = new CodeBlock();
			root->toPrettyCode(context);	
			std::cout << context->toPrettyCode();
		}
		
		/*
		if(PARSE_SIMBOLS != NULL){
			SymbolTable *st = SymbolTable::Instance();
			std::cout << st->toStdString() << std::endl;
		}
		*/
		
		if (GENERATE_CODE != NULL){
			/** will generate code */
			CodeContext *context = new CodeContext();
			root->generateCode(context);
			std::cout << context->buffer.str() << std::endl;
		}
	}
	
	return parse_result;
}