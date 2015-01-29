#include <iostream>
#include <vector>

class Node {
	public:
		virtual ~Node() {}
		virtual std::string toStdString() = 0;
		virtual std::string toPrettyCode(){ return ""; };
};

class Expression : public Node {

};

typedef std::vector<Expression*> ExpressionList;

class Operator : public Expression {
	public:
		std::string value;
	
		Operator(std::string value) : value(value) {}
		std::string toStdString();
		std::string toPrettyCode();
};

class ConstantExpression : public Expression {
	
};

class Identifier : public Expression {
	public:
		std::string value;
	
		Identifier(std::string value) : value(value){}
		std::string toStdString();
		std::string toPrettyCode();
};

class Constant : public Expression {
	public:
		std::string value;
	
		Constant(std::string value) : value(value){}
		std::string toStdString();
		std::string toPrettyCode();
};

class StringLiteral : public Expression {
	public:
		std::string value;
	
		StringLiteral(std::string value) : value(value){}
		std::string toStdString();
		std::string toPrettyCode();
};

typedef std::vector<Identifier*> IdentifierList;

class PrimaryExpression : public Expression {
	public:
		ExpressionList expression_list;
		PrimaryExpression(ExpressionList expression_list) : expression_list(expression_list) {}
	
		virtual std::string toStdString();
		std::string toPrettyCode();
};

class PostfixOperation : public Expression {
	public:
		Expression *operand = NULL;
		Operator *unary_operator = NULL;
	
		PostfixOperation(Expression *operand, Operator *unary_operator) :
			operand(operand), unary_operator(unary_operator) {}
	
		virtual std::string toStdString();
		std::string toPrettyCode();
};

class ArrayAccess : public Expression {
	public:
		Expression *postfix_expression = NULL;
		ExpressionList expression;
	
		ArrayAccess(Expression *postfix_expression,ExpressionList expression):
			postfix_expression(postfix_expression),
			expression(expression){}
	
		std::string toStdString();
		std::string toPrettyCode();
};

class FunctionCall : public Expression {
  public:
    Expression *postifx_expression = NULL;
    ExpressionList argument_expression_list;
  
    FunctionCall(Expression *postifx_expression) : postifx_expression(postifx_expression){}
    FunctionCall(Expression *postifx_expression, ExpressionList argument_expression_list) : 
      postifx_expression(postifx_expression),
      argument_expression_list(argument_expression_list) {}
  
    std::string toStdString();
	std::string toPrettyCode();
};

class UnaryOperation : public Expression {
	public:
		Expression *operand = NULL;
		Operator *unary_operator = NULL;
	
		UnaryOperation(Expression *operand, Operator *unary_operator) :
			operand(operand), unary_operator(unary_operator) {}
	
		std::string toStdString();
		std::string toPrettyCode();
};

class BinaryOperation : public Expression {
	public:
		Expression *right_operand = NULL;
		Expression *left_operand = NULL;
		Operator *binary_operator = NULL;
	
		BinaryOperation(Expression *left_operand, Operator *binary_operator, Expression *right_operand) :
			right_operand(right_operand),
			binary_operator(binary_operator),
			left_operand(left_operand) {}
			
		virtual std::string toStdString();
		std::string toPrettyCode();
};

class ConditionalExpression : public Expression {
	public: 
		Expression *logical_or_expression = NULL;
		ExpressionList expression; 
		Expression *conditional_expression = NULL;
	
		ConditionalExpression(Expression *logical_or_expression,
							ExpressionList expression,
							Expression *conditional_expression) :
		logical_or_expression(logical_or_expression),
		expression(expression),
		conditional_expression(conditional_expression) {}
	
		std::string toStdString();
		std::string toPrettyCode();
};

class AssignmentExpression : public Expression {
	public:
		Operator *assignment_operator = NULL;
		Expression *unary_expression = NULL;
		Expression *assignment_expression = NULL;
	
		AssignmentExpression(Expression *unary_expression, 
							 Operator *assignment_operator, 
							 Expression *assignment_expression) :
			unary_expression(unary_expression), 
			assignment_operator(assignment_operator),
			assignment_expression(assignment_expression) {}
	
		virtual std::string toStdString();
		std::string toPrettyCode();
};

class Statement : public Node {
	
};

typedef std::vector<Statement*> StatementList;

class TranslationUnit : public Expression {
	public:
		StatementList statements;
		std::string toStdString();
		std::string toPrettyCode();
};

class DeclarationSpecifier : public Statement {
	
};

typedef std::vector<DeclarationSpecifier*> DeclarationSpecifierList;

class StorageClassSpecifier : public DeclarationSpecifier {
	public:
		int token;
		std::string value;
	
		StorageClassSpecifier(int token, std::string value) 
			: token(token), value(value) { }
		
		std::string toStdString();
		std::string toPrettyCode();
};

class TypeSpecifier : public DeclarationSpecifier {
	public:
		int token;
		std::string value;
	
		TypeSpecifier(int token, std::string value) 
			: token(token), value(value) {}
		
		std::string toStdString();
		std::string toPrettyCode();
};

class TypeQualifier : public DeclarationSpecifier {
	public:
		int token;
		std::string value;
	
		TypeQualifier(int token, std::string value) 
			: token(token), value(value) {}
		std::string toStdString();
		std::string toPrettyCode();
};

typedef std::vector<TypeQualifier*> TypeQualifierList;

class DirectDeclarator : public Statement {
	
};

class IdentifierDeclarator : public DirectDeclarator {
	public:
		std::string identifier;
	
		IdentifierDeclarator(std::string identifier) : identifier(identifier) {}
		std::string toStdString();
		std::string toPrettyCode();
};

class ArrayDeclarator : public DirectDeclarator {
	public:
		DirectDeclarator *direct_declarator = NULL;
		Expression *constant_expression = NULL;
	
		ArrayDeclarator(DirectDeclarator *direct_declarator) : direct_declarator(direct_declarator) {}
		ArrayDeclarator(DirectDeclarator *direct_declarator, Expression *constant_expression) : 
			direct_declarator(direct_declarator), constant_expression(constant_expression) {}
		std::string toStdString();
		std::string toPrettyCode();
};

class Declarator;

class ParameterDeclaration : public Statement {
	public:
		DeclarationSpecifierList declaration_specifiers;
		Declarator *declarator = NULL;
	
		ParameterDeclaration(DeclarationSpecifierList declaration_specifiers, Declarator *declarator) :
			declaration_specifiers(declaration_specifiers), declarator(declarator) {}
	
		ParameterDeclaration(DeclarationSpecifierList declaration_specifiers) :
			declaration_specifiers(declaration_specifiers) {}
	
		virtual std::string toStdString();
		std::string toPrettyCode();
};

typedef std::vector<ParameterDeclaration*> ParameterDeclarationList;

class FunctionDeclarator : public DirectDeclarator {
	public:
		DirectDeclarator *direct_declarator = NULL;
		IdentifierList identifier_list;
		ParameterDeclarationList parameter_type_list;
	
		FunctionDeclarator(DirectDeclarator *direct_declarator) : direct_declarator(direct_declarator) {}
		FunctionDeclarator(DirectDeclarator *direct_declarator, IdentifierList identifier_list) : 
			direct_declarator(direct_declarator), identifier_list(identifier_list) {}
		FunctionDeclarator(DirectDeclarator *direct_declarator, ParameterDeclarationList parameter_type_list) : 
			direct_declarator(direct_declarator), parameter_type_list(parameter_type_list) {}
		std::string toStdString();
		std::string toPrettyCode();
};

class Pointer : public Statement {
	public:
		TypeQualifierList type_qualifier_list;
		Pointer *child = NULL;
	
		Pointer() {}
	
		Pointer(Pointer *child) : child(child) {}
	
		Pointer(TypeQualifierList type_qualifier_list) : type_qualifier_list(type_qualifier_list) {}
	
		Pointer(TypeQualifierList type_qualifier_list, Pointer *child) :
			child(child), type_qualifier_list(type_qualifier_list) {}
	
		std::string toStdString();
		std::string toPrettyCode();
};

class Declarator : public Statement {
	public:
		Pointer *pointer = NULL;
		DirectDeclarator *direct_declarator = NULL;
	
		Declarator(DirectDeclarator *direct_declarator) : direct_declarator(direct_declarator){}
  
		Declarator(Pointer *pointer, DirectDeclarator *direct_declarator) : 
			pointer(pointer), direct_declarator(direct_declarator){}
	
		virtual std::string toStdString();
		std::string toPrettyCode();
};

class NestedDeclarator : public DirectDeclarator {
	public:
		Declarator *declarator = NULL;
	
		NestedDeclarator(Declarator *declarator) : declarator(declarator) {}
		virtual std::string toStdString();
};

class Initializer : public Statement {
	public:
		Expression *assignment_expression = NULL;
	
		Initializer(Expression *assignment_expression) :
			assignment_expression(assignment_expression) {}
		virtual std::string toStdString();
		std::string toPrettyCode();
};

class InitDeclarator : public Statement {
	public:
		Declarator *declarator = NULL;
		Initializer *initializer = NULL;
	
		InitDeclarator(Declarator *declarator) : declarator(declarator) {}
		InitDeclarator(Declarator *declarator, Initializer *initializer) : 
			declarator(declarator),
			initializer(initializer) {}
	
		std::string toStdString();
		std::string toPrettyCode();
};

typedef std::vector<InitDeclarator*> InitDeclaratorList;

class Declaration : public Statement {
	public:
		DeclarationSpecifierList specifiers;
		InitDeclaratorList declarators;	
	
		Declaration(DeclarationSpecifierList specifiers) : specifiers(specifiers) {}
		Declaration(DeclarationSpecifierList specifiers, InitDeclaratorList declarators) : 
			specifiers(specifiers), declarators(declarators) {}
	
		virtual std::string toStdString();
		std::string toPrettyCode();
};

typedef std::vector<Declaration*> DeclarationList;

class LabeledStatement : public Statement {
	public:
		virtual std::string toStdString();
};

class CompoundStatement : public Statement {
	public:
		StatementList statement_list;
		DeclarationList declaration_list;
	
		CompoundStatement(){}
	
		CompoundStatement(StatementList statement_list) : statement_list(statement_list) {}
	
		CompoundStatement(DeclarationList declaration_list) : declaration_list(declaration_list) {}
	
		CompoundStatement(DeclarationList declaration_list, StatementList statement_list) :
			statement_list(statement_list), declaration_list(declaration_list) {}
	
		virtual std::string toStdString();
		std::string toPrettyCode();
};

class ExpressionStatement : public Statement {
	public:
		ExpressionList expression_list;
	
		ExpressionStatement(ExpressionList expression_list) : 
			expression_list(expression_list) {}
  
        ExpressionStatement(){}
	
		virtual std::string toStdString();
		std::string toPrettyCode();
};

class SelectionStatement : public Statement {
	public:
		virtual std::string toStdString();
};

class IterationStatement : public Statement {
	public:
		virtual std::string toStdString();
};

class JumpStatement : public Statement {
	public:
		int token;
		std::string identifier;
		ExpressionList expression_list;
	
		JumpStatement(int token) : token(token) {}
		JumpStatement(int token, std::string identifier) : 
			token(token),
			identifier(identifier){}
		JumpStatement(int token, ExpressionList expression_list) :
			token(token),
			expression_list(expression_list) {}
	
		virtual std::string toStdString();
		std::string toPrettyCode();
};

class FunctionDefinition : public Statement {
	public:
		DeclarationSpecifierList declaration_specifier_list;
		Declarator *declarator = NULL;
		DeclarationList declaration_list;
		CompoundStatement *compound_statement = NULL;
		
		FunctionDefinition(DeclarationSpecifierList declaration_specifier_list, Declarator *declarator, DeclarationList declaration_list, CompoundStatement *compound_statement) :
			declaration_specifier_list(declaration_specifier_list), 
			declarator(declarator), 
			declaration_list(declaration_list), 
			compound_statement(compound_statement) {}
	
		FunctionDefinition(Declarator *declarator, CompoundStatement *compound_statement) :
			declarator(declarator), compound_statement(compound_statement) {}
		
		FunctionDefinition(Declarator *declarator, DeclarationList declaration_list, CompoundStatement *compound_statement) :
			declarator(declarator), declaration_list(declaration_list), compound_statement(compound_statement) {}
	
		FunctionDefinition(DeclarationSpecifierList declaration_specifier_list, Declarator *declarator, CompoundStatement *compound_statement) :
			declaration_specifier_list(declaration_specifier_list), declarator(declarator), compound_statement(compound_statement) {}
		
		virtual std::string toStdString();
		std::string toPrettyCode();
};
