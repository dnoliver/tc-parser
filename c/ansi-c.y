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
	StatementList *statement_list;
	Declaration *declaration;
	ParameterDeclaration *parameter_declaration;
	ParameterDeclarationList *parameter_list;
	DeclarationSpecifierList *declaration_specifiers;
	StorageClassSpecifier *storage_class_specifier;
	TypeSpecifier *type_specifier;
	TypeQualifier *type_qualifier;
	InitDeclaratorList *init_declarator_list;
	InitDeclarator *init_declarator;
	Declarator *declarator;
	
	
	ConstantExpression *constant_expression;
	
	DirectDeclarator *direct_declarator;
	IdentifierDeclarator *identifier_declarator;
	
	Pointer *pointer;
	FunctionDefinition *function_definition;
	DeclarationList *declaration_list;
	CompoundStatement *compound_statement;
	TypeQualifierList *type_qualifier_list;
	
	std::string *string;
	IdentifierList *identifier_list;
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
%type <statement> external_declaration statement
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
%type <function_definition> function_definition
%type <compound_statement> compound_statement
%type <declaration_list> declaration_list
%type <statement_list> statement_list
%type <type_qualifier_list> type_qualifier_list
%type <identifier_list> identifier_list
%type <constant_expression> constant_expression
%type <parameter_declaration> parameter_declaration
%type <parameter_list> parameter_list parameter_type_list

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
	: conditional_expression { $$ = new ConstantExpression(); }
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

/** not implemented */
struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

/** not implemented */
struct_or_union
	: STRUCT
	| UNION
	;

/** not implemented */
struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

/** not implemented */
struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

/** not implemented */
specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

/** not implemented */
struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

/** not implemented */
struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

/** not implemented */
enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

/** not implemented */
enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;
/** not implemented */
enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST { $$ = new TypeQualifier(CONST, "const"); }
	| VOLATILE { $$ = new TypeQualifier(VOLATILE, "volatile"); }
	;

declarator
	: pointer direct_declarator { $$ = new Declarator($1,$2); }
	| direct_declarator { $$ = new Declarator($1); }
	;

direct_declarator
	: IDENTIFIER { $$ = new IdentifierDeclarator(*$1); delete $1; }
	| '(' declarator ')' { $$ = new NestedDeclarator($2); }
	| direct_declarator '[' constant_expression ']' { $$ = new ArrayDeclarator($1,$3); }
	| direct_declarator '[' ']' { $$ = new ArrayDeclarator($1); }
	| direct_declarator '(' parameter_type_list ')' { $$ = new FunctionDeclarator($1,*$3); }
	| direct_declarator '(' identifier_list ')' { $$ = new FunctionDeclarator($1,*$3); }
	| direct_declarator '(' ')' { $$ = new FunctionDeclarator($1); }
	;

pointer
	: '*' { $$ = new Pointer(); }
	| '*' type_qualifier_list { $$ = new Pointer(*$2); }
	| '*' pointer { $$ = new Pointer($2); }
	| '*' type_qualifier_list pointer { $$ = new Pointer(*$2,$3); }
	;

type_qualifier_list
	: type_qualifier { $$ = new TypeQualifierList(); $$->push_back($1); }
	| type_qualifier_list type_qualifier { $1->push_back($2); $$ = $1;}
	;


parameter_type_list
	: parameter_list 
	| parameter_list ',' ELLIPSIS /** not implemented */
	;

parameter_list
	: parameter_declaration { $$ = new ParameterDeclarationList(); $$->push_back($1); }
	| parameter_list ',' parameter_declaration { $1->push_back($3); $$ = $1; }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = new ParameterDeclaration(*$1,$2); }
	| declaration_specifiers abstract_declarator /** not implemented */
	| declaration_specifiers { $$ = new ParameterDeclaration(*$1); }
	;

identifier_list
	: IDENTIFIER { $$ = new IdentifierList(); $$->push_back($1); }
	| identifier_list ',' IDENTIFIER { $1->push_back($3), $$ = $1; }
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
	: labeled_statement 	/** @returns LabeledStatement */
	| compound_statement	/** @returns CompoundStatement */
	| expression_statement	/** @returns ExpressionStatement */
	| selection_statement	/** @returns SelectionStatement */
	| iteration_statement	/** @returns IterationStatement */
	| jump_statement		/** @returns JumpStatement */
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}' { $$ = new CompoundStatement(); }
	| '{' statement_list '}' { $$ = new CompoundStatement(*$2); }
	| '{' declaration_list '}' { $$ = new CompoundStatement(*$2); }
	| '{' declaration_list statement_list '}' { $$ = new CompoundStatement(*$2,*$3); }
	;

declaration_list
	: declaration { $$ = new DeclarationList(); $$->push_back($1); }
	| declaration_list declaration { $1->push_back($2); $$ = $1; }
	;

statement_list
	: statement { $$ = new StatementList(); $$->push_back($1); }
	| statement_list statement { $1->push_back($2); $$ = $1; }
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
	| translation_unit external_declaration { $1->statements.push_back($<statement>2); $$ = $1; }
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement { $$ = new FunctionDefinition(*$1,$2,*$3,$4); }
	| declaration_specifiers declarator compound_statement { $$ = new FunctionDefinition(*$1,$2,$3); }
	| declarator declaration_list compound_statement { $$ = new FunctionDefinition($1,*$2,$3); }
	| declarator compound_statement { $$ = new FunctionDefinition($1,$2); }
	;

%%