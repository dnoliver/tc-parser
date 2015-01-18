%{
	#include "node.hpp"
	#include <stdio.h>

	TranslationUnit *root; /* the top level root node of our final AST */
	extern char yytext[];
	extern int column;
	extern int yylex();

	void yyerror(char *s)
	{
		fflush(stdout);
		printf("\n%*s\n%*s\n", column, "^", column, s);
	}
%}

%union {
	Node *node;
	TranslationUnit *translation_unit;
	Statement *statement;
	Declaration *declaration;
	DeclarationSpecifierList *declaration_specifiers;
	StorageClassSpecifier *storage_class_specifier;
	TypeSpecifier *type_specifier;
	TypeQualifier *type_qualifier;
	InitDeclaratorList *init_declarator_list;
	InitDeclarator *init_declarator;
	Declarator *declarator;
	DirectDeclarator *direct_declarator;
	PointerDeclarator *pointer;
	PointerDirectDeclarator *pointer_direct_declarator;
	
	std::string *string;
	int token;
}

%token <string> IDENTIFIER
%token CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an identifier (defined by union type idententifier) we are really
   calling an (NodeIdentifier*). It makes the compiler happy.
 */
%type <translation_unit> program translation_unit
%type <statement> external_declaration
%type <declaration> declaration
%type <declaration_specifiers> declaration_specifiers
%type <storage_class_specifier> storage_class_specifier
%type <type_specifier> type_specifier
%type <type_qualifier> type_qualifier
%type <init_declarator_list> init_declarator_list
%type <init_declarator> init_declarator
%type <declarator> declarator
%type <direct_declarator> direct_declarator
%type <pointer> pointer

%start program
%%

primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';' { $$ = new Declaration(*$1); }
	| declaration_specifiers init_declarator_list ';' { $$ = new Declaration(*$1,*$2); }
	;

declaration_specifiers
	: storage_class_specifier { $$ = new DeclarationSpecifierList(); $$->push_back($1); }
	| storage_class_specifier declaration_specifiers { $2->push_back($1); $$ = $2; }
	| type_specifier { $$ = new DeclarationSpecifierList(); $$->push_back($1); }
	| type_specifier declaration_specifiers { $2->push_back($1); $$ = $2; }
	| type_qualifier { $$ = new DeclarationSpecifierList(); $$->push_back($1); }
	| type_qualifier declaration_specifiers { $2->push_back($1); $$ = $2; }
	;

init_declarator_list
	: init_declarator { $$ = new InitDeclaratorList(); $$->push_back($1); }
	| init_declarator_list ',' init_declarator { $1->push_back($3), $$ = $1; }
	;

init_declarator
	: declarator { $$ = new InitDeclarator($1); }
	| declarator '=' initializer
	;

storage_class_specifier
	: TYPEDEF { $$ = new StorageClassSpecifier(TYPEDEF, "typedef"); }
	| EXTERN { $$ = new StorageClassSpecifier(EXTERN, "extern"); }
	| STATIC { $$ = new StorageClassSpecifier(STATIC, "static"); }
	| AUTO { $$ = new StorageClassSpecifier(AUTO, "auto"); }
	| REGISTER { $$ = new StorageClassSpecifier(REGISTER, "register"); }
	;

type_specifier
	: VOID { $$ = new TypeSpecifier(VOID, "void"); }
	| CHAR { $$ = new TypeSpecifier(CHAR, "char"); }
	| SHORT { $$ = new TypeSpecifier(SHORT, "short"); }
	| INT { $$ = new TypeSpecifier(INT, "int"); }
	| LONG { $$ = new TypeSpecifier(LONG, "long"); }
	| FLOAT { $$ = new TypeSpecifier(FLOAT, "float"); }
	| DOUBLE { $$ = new TypeSpecifier(DOUBLE, "double"); }
	| SIGNED { $$ = new TypeSpecifier(SIGNED, "signed"); }
	| UNSIGNED { $$ = new TypeSpecifier(UNSIGNED, "unsigned"); }
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST { $$ = new TypeQualifier(CONST, "const"); }
	| VOLATILE { $$ = new TypeQualifier(VOLATILE, "volatile"); }
	;

declarator
	: pointer direct_declarator { $$ = new PointerDirectDeclarator($1,$2); }
	| direct_declarator
	;

direct_declarator
	: IDENTIFIER { $$ = new DirectDeclarator(*$1); delete $1; }
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

pointer
	: '*' { $$ = new PointerDeclarator(); }
	| '*' type_qualifier_list
	| '*' pointer { $$ = new PointerDeclarator($2); }
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

program: translation_unit { root = $1; }
	;

translation_unit
	: external_declaration { $$ = new TranslationUnit(); $$->statements.push_back($<statement>1); }
	| translation_unit external_declaration { $1->statements.push_back($<statement>2); }
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%