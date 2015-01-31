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
	Initializer *initializer;
	Declarator *declarator;
	
	Expression *expression;
	ExpressionList *expression_list;
    ExpressionStatement *expression_statement;
	
	Operator *op;
	
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

%token <string> IDENTIFIER CONSTANT STRING_LITERAL
%token SIZEOF
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
%type <statement> external_declaration statement jump_statement labeled_statement
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
%type <parameter_declaration> parameter_declaration
%type <parameter_list> parameter_list parameter_type_list
%type <expression_list> expression argument_expression_list
%type <expression> constant_expression assignment_expression unary_expression postfix_expression primary_expression
%type <expression> conditional_expression logical_or_expression logical_and_expression
%type <expression> inclusive_or_expression exclusive_or_expression
%type <expression> and_expression equality_expression relational_expression shift_expression
%type <expression> additive_expression multiplicative_expression cast_expression
%type <op> assignment_operator
%type <initializer> initializer
%type <expression_statement> expression_statement

%start program
%%

primary_expression
	: IDENTIFIER 			{ $$ = new Identifier(*$1); delete $1; }
	| CONSTANT				{ $$ = new Constant(*$1); delete $1; }
	| STRING_LITERAL		{ $$ = new StringLiteral(*$1); delete $1; }
	| '(' expression ')'	{ $$ = new PrimaryExpression(*$2); }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']'					{ $$ = new ArrayAccess($1,*$3); }
	| postfix_expression '(' ')'							{ $$ = new FunctionCall($1); }
	| postfix_expression '(' argument_expression_list ')'	{ $$ = new FunctionCall($1,*$3); }
	| postfix_expression '.' IDENTIFIER 					/** not implemented */
	| postfix_expression PTR_OP IDENTIFIER  				/** not implemented */
	| postfix_expression INC_OP								{ $$ = new PostfixOperation($1,new Operator("++")); }
	| postfix_expression DEC_OP								{ $$ = new PostfixOperation($1,new Operator("--")); }
	;

argument_expression_list
	: assignment_expression { $$ = new ExpressionList(); $$->push_back($1); }
	| argument_expression_list ',' assignment_expression { $1->push_back($3); $$ = $1; }
	;

unary_expression
	: postfix_expression 				{ $$ = $1; }
	| INC_OP unary_expression 			{ $$ = new UnaryOperation($2,new Operator("++")); }
	| DEC_OP unary_expression 			{ $$ = new UnaryOperation($2,new Operator("--")); }
	| unary_operator cast_expression 	/** not implemented */
	| SIZEOF unary_expression 			{ $$ = new UnaryOperation($2,new Operator("sizeof")); }
	| SIZEOF '(' type_name ')' 			/** not implemented */
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
	: unary_expression 					{ $$ = $1; }
	| '(' type_name ')' cast_expression	/** not implemented */
	;

multiplicative_expression
	: cast_expression 								{ $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = new BinaryOperation($1,new Operator("*"),$3); }
	| multiplicative_expression '/' cast_expression { $$ = new BinaryOperation($1,new Operator("/"),$3); }
	| multiplicative_expression '%' cast_expression { $$ = new BinaryOperation($1,new Operator("%"),$3); }
	;

additive_expression
	: multiplicative_expression 						{ $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = new BinaryOperation($1,new Operator("+"),$3); }
	| additive_expression '-' multiplicative_expression { $$ = new BinaryOperation($1,new Operator("-"),$3); }
	;

shift_expression
	: additive_expression 							{ $$ = $1; } 
	| shift_expression LEFT_OP additive_expression 	{ $$ = new BinaryOperation($1,new Operator("<<"),$3); }
	| shift_expression RIGHT_OP additive_expression { $$ = new BinaryOperation($1,new Operator(">>"),$3); }
	;

relational_expression
	: shift_expression 								{ $$ = $1; }
	| relational_expression '<' shift_expression 	{ $$ = new BinaryOperation($1,new Operator("<"),$3); }
	| relational_expression '>' shift_expression 	{ $$ = new BinaryOperation($1,new Operator(">"),$3); }
	| relational_expression LE_OP shift_expression 	{ $$ = new BinaryOperation($1,new Operator("<="),$3); }
	| relational_expression GE_OP shift_expression 	{ $$ = new BinaryOperation($1,new Operator(">="),$3); }
	;

equality_expression
	: relational_expression								{ $$ = $1; }
	| equality_expression EQ_OP relational_expression 	{ $$ = new BinaryOperation($1,new Operator("=="),$3); }
	| equality_expression NE_OP relational_expression 	{ $$ = new BinaryOperation($1,new Operator("!="),$3); }
	;

and_expression
	: equality_expression 						{ $$ = $1; }
	| and_expression '&' equality_expression 	{ $$ = new BinaryOperation($1,new Operator("&"),$3); }
	;

exclusive_or_expression
	: and_expression 								{ $$ = $1; }
	| exclusive_or_expression '^' and_expression 	{ $$ = new BinaryOperation($1,new Operator("^"),$3); }
	;

inclusive_or_expression
	: exclusive_or_expression 								{ $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression 	{ $$ = new BinaryOperation($1,new Operator("|"),$3); }
	;

logical_and_expression
	: inclusive_or_expression 								{ $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ = new BinaryOperation($1,new Operator("&&"),$3); }
	;

logical_or_expression
	: logical_and_expression 								{ $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression 	{ $$ = new BinaryOperation($1,new Operator("||"),$3); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ = new ConditionalExpression($1,*$3,$5); }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression { $$ = new AssignmentExpression($1,$2,$3); }
	;

assignment_operator
	: '=' 			{ $$ = new Operator("="); }
	| MUL_ASSIGN	{ $$ = new Operator("*="); }
	| DIV_ASSIGN	{ $$ = new Operator("/="); }
	| MOD_ASSIGN	{ $$ = new Operator("%="); }
	| ADD_ASSIGN	{ $$ = new Operator("+="); }
	| SUB_ASSIGN	{ $$ = new Operator("-="); }
	| LEFT_ASSIGN	{ $$ = new Operator("<<="); }
	| RIGHT_ASSIGN	{ $$ = new Operator(">>="); }
	| AND_ASSIGN	{ $$ = new Operator("&="); }
	| XOR_ASSIGN	{ $$ = new Operator("^="); }
	| OR_ASSIGN		{ $$ = new Operator("|="); }
	;

expression
	: assignment_expression { $$ = new ExpressionList(); $$->push_back($1); }
	| expression ',' assignment_expression { $1->push_back($3); $$ = $1; }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

declaration
	: declaration_specifiers ';' { $$ = new Declaration(*$1); }
	| declaration_specifiers init_declarator_list ';' { $$ = new Declaration(*$1,*$2); }
	;

declaration_specifiers
	: storage_class_specifier 							{ $$ = new DeclarationSpecifierList(); $$->insert($$->begin(),$1); }
	| storage_class_specifier declaration_specifiers 	{ $2->insert($2->begin(),$1); $$ = $2; }
	| type_specifier 									{ $$ = new DeclarationSpecifierList(); $$->insert($$->begin(),$1); }
	| type_specifier declaration_specifiers 			{ $2->insert($2->begin(),$1); $$ = $2; }
	| type_qualifier 									{ $$ = new DeclarationSpecifierList(); $$->insert($$->begin(),$1); }
	| type_qualifier declaration_specifiers 			{ $2->insert($2->begin(),$1); $$ = $2; }
	;

init_declarator_list
	: init_declarator { $$ = new InitDeclaratorList(); $$->push_back($1); }
	| init_declarator_list ',' init_declarator { $1->push_back($3), $$ = $1; }
	;

init_declarator
	: declarator { $$ = new InitDeclarator($1); }
	| declarator '=' initializer { $$ = new InitDeclarator($1,$3); }
	;

storage_class_specifier
	: TYPEDEF 	{ $$ = new StorageClassSpecifier(TYPEDEF, "typedef"); }
	| EXTERN 	{ $$ = new StorageClassSpecifier(EXTERN, "extern"); }
	| STATIC 	{ $$ = new StorageClassSpecifier(STATIC, "static"); }
	| AUTO 		{ $$ = new StorageClassSpecifier(AUTO, "auto"); }
	| REGISTER 	{ $$ = new StorageClassSpecifier(REGISTER, "register"); }
	;

type_specifier
	: VOID 		{ $$ = new TypeSpecifier(VOID, "void"); }
	| CHAR 		{ $$ = new TypeSpecifier(CHAR, "char"); }
	| SHORT 	{ $$ = new TypeSpecifier(SHORT, "short"); }
	| INT 		{ $$ = new TypeSpecifier(INT, "int"); }
	| LONG 		{ $$ = new TypeSpecifier(LONG, "long"); }
	| FLOAT 	{ $$ = new TypeSpecifier(FLOAT, "float"); }
	| DOUBLE 	{ $$ = new TypeSpecifier(DOUBLE, "double"); }
	| SIGNED 	{ $$ = new TypeSpecifier(SIGNED, "signed"); }
	| UNSIGNED 	{ $$ = new TypeSpecifier(UNSIGNED, "unsigned"); }
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
	: CONST 	{ $$ = new TypeQualifier(CONST, "const"); }
	| VOLATILE 	{ $$ = new TypeQualifier(VOLATILE, "volatile"); }
	;

declarator
	: pointer direct_declarator { $$ = new PointerDeclarator($1,$2); }
	| direct_declarator 		{ $$ = $1; }
	;

direct_declarator
	: IDENTIFIER 									{ $$ = new IdentifierDeclarator(new Identifier(*$1)); delete $1; }
	| '(' declarator ')' 							{ $$ = new NestedDeclarator($2); }
	| direct_declarator '[' constant_expression ']' { $$ = new ArrayDeclarator($1,$3); }
	| direct_declarator '[' ']' 					{ $$ = new ArrayDeclarator($1); }
	| direct_declarator '(' parameter_type_list ')' { $$ = new FunctionDeclarator($1,*$3); }
	| direct_declarator '(' identifier_list ')' 	{ $$ = new FunctionDeclarator($1,*$3); }
	| direct_declarator '(' ')' 					{ $$ = new FunctionDeclarator($1); }
	;

pointer
	: '*' 									{ $$ = new Pointer(); }
	| '*' type_qualifier_list 				{ $$ = new Pointer(*$2); }
	| '*' pointer 							{ $$ = new Pointer($2); }
	| '*' type_qualifier_list pointer 		{ $$ = new Pointer(*$2,$3); }
	;

type_qualifier_list
	: type_qualifier 						{ $$ = new TypeQualifierList(); $$->push_back($1); }
	| type_qualifier_list type_qualifier 	{ $1->push_back($2); $$ = $1;}
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
	: declaration_specifiers declarator          { $$ = new ParameterDeclaration(*$1,$2); }
	| declaration_specifiers abstract_declarator /* not implemented */
	| declaration_specifiers                     { $$ = new ParameterDeclaration(*$1); }
	;

identifier_list
	: IDENTIFIER 						{ $$ = new IdentifierList(); $$->push_back(new Identifier(*$1)); }
	| identifier_list ',' IDENTIFIER 	{ $1->push_back(new Identifier(*$3)), $$ = $1; }
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
	: assignment_expression 		{ $$ = new Initializer($1); }
	| '{' initializer_list '}'		/** not implemented */
	| '{' initializer_list ',' '}'	/** not implemented */
	;

initializer_list
	: initializer						/** not implemented */
	| initializer_list ',' initializer	/** not implemented */
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
	: IDENTIFIER ':' statement					{ $$ = new TaggedStatement(new IdentifierDeclarator(new Identifier(*$1)),$3); }
	| CASE constant_expression ':' statement	{ $$ = new CaseStatement($2,$4); }
	| DEFAULT ':' statement						{ $$ = new DefaultStatement($3); }
	;

compound_statement
	: '{' '}' 									{ $$ = new CompoundStatement(); }
	| '{' statement_list '}' 					{ $$ = new CompoundStatement(*$2); }
	| '{' declaration_list '}' 					{ $$ = new CompoundStatement(*$2); }
	| '{' declaration_list statement_list '}' 	{ $$ = new CompoundStatement(*$2,*$3); }
	;

declaration_list
	: declaration 					{ $$ = new DeclarationList(); $$->push_back($1); }
	| declaration_list declaration 	{ $1->push_back($2); $$ = $1; }
	;

statement_list
	: statement 				{ $$ = new StatementList(); $$->push_back($1); }
	| statement_list statement 	{ $1->push_back($2); $$ = $1; }
	;

expression_statement
	: ';'            { $$ = new ExpressionStatement(); }
	| expression ';' { $$ = new ExpressionStatement(*$1); }
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
	: GOTO IDENTIFIER ';'	{ $$ = new JumpStatement(GOTO,*$2); delete $2; }
	| CONTINUE ';' 			{ $$ = new JumpStatement(CONTINUE); }
	| BREAK ';'				{ $$ = new JumpStatement(BREAK); }
	| RETURN ';'			{ $$ = new JumpStatement(RETURN); }
	| RETURN expression ';'	{ $$ = new JumpStatement(RETURN, *$2); delete $2; }
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