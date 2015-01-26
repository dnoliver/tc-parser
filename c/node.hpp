#include <iostream>
#include <vector>

class Node {
	public:
		virtual ~Node() {}
		virtual std::string toStdString(){}
};

class Expression : public Node {
	public:
		virtual std::string toStdString(){}
};

typedef std::vector<Expression*> ExpressionList;

class ConstantExpression : public Expression {
	public:
		virtual std::string toStdString(){ return "<ConstantExpression></ConstantExpression>"; }
};

class PrimaryExpression : public Expression {
	public:
		int token;
		std::string value;
		ExpressionList expression_list;
	
		PrimaryExpression(int token, std::string value) : token(token), value(value) {}
		PrimaryExpression(ExpressionList expression_list) : expression_list(expression_list) {}
	
		virtual std::string toStdString(){ 
			std::string result = "<PrimaryExpression value='" + value + "'>";
			result += "</PrimaryExpression>"; 
			
			return result;
		}
};

class PostfixOperation : public Expression {
	public:
		Expression *operand;
		int unary_operator;
	
		PostfixOperation(Expression *operand, int unary_operator) :
			operand(operand), unary_operator(unary_operator) {}
	
		virtual std::string toStdString(){
			std::string result = "<PostfixOperation operator='" + std::to_string(unary_operator) + "'>";
			
			if(operand != NULL){
				result += operand->toStdString();
			}
			
			result += "</PostfixOperation>";
			return result;
		}
};

class UnaryOperation : public Expression {
	public:
		Expression *operand;
		int unary_operator;
	
		UnaryOperation(Expression *operand, int unary_operator) :
			operand(operand), unary_operator(unary_operator) {}
	
		virtual std::string toStdString(){
			std::string result = "<UnaryOperation operator='" + std::to_string(unary_operator) + "'>";
			
			if(operand != NULL){
				result += operand->toStdString();
			}
			
			result += "</UnaryOperation>";
			return result;
		}
};

class BinaryOperation : public Expression {
	public:
		Expression *right_operand;
		Expression *left_operand;
		int binary_operator;
	
		BinaryOperation(Expression *left_operand, int binary_operator, Expression *right_operand) :
			right_operand(right_operand),
			binary_operator(binary_operator),
			left_operand(left_operand) {}
			
		virtual std::string toStdString(){
			std::string result = "<BinaryOperation operator='" + std::to_string(binary_operator) + "'>";
			
			if(left_operand != NULL){
				result += left_operand->toStdString();
			}
			
			if(right_operand != NULL){
				result += right_operand->toStdString();
			}
			
			result += "</BinaryOperation>";
			return result;
		}
};

class ConditionalExpression : public Expression {
	public: 
		Expression *logical_or_expression;
		ExpressionList expression; 
		Expression *conditional_expression;
	
		ConditionalExpression(Expression *logical_or_expression,
							ExpressionList expression,
							Expression *conditional_expression) :
		logical_or_expression(logical_or_expression),
		expression(expression),
		conditional_expression(conditional_expression) {}
	
		virtual std::string toStdString(){
			std::string result = "<ConditionalExpression>";
			
			if(logical_or_expression != NULL){
				result += logical_or_expression->toStdString();
			}
			
			if(expression.size() != 0){
				result += "<ExpressionList>";
				for( auto &i : expression ) {
					result += i->toStdString();
				}
				result += "</ExpressionList>";	
			}
			
			if(conditional_expression != NULL){
				result += conditional_expression->toStdString();
			}
			
			result += "</ConditionalExpression>";
			return result;
		}
};

class AssignmentOperator : public Expression {
	public:
		int token;
	
		AssignmentOperator(int token) : token(token) {}
		virtual std::string toStdString(){ return "<AssignmentOperator></AssignmentOperator>"; }
};

class AssignmentExpression : public Expression {
	public:
		AssignmentOperator *assignament_operator;
		Expression *unary_expression;
		Expression *assignment_expression;
	
		AssignmentExpression(Expression *unary_expression, 
							 AssignmentOperator *assignment_expression, 
							 Expression *assignament_expression) :
			unary_expression(unary_expression), 
			assignament_operator(assignament_operator),
			assignment_expression(assignment_expression) {}
	
		virtual std::string toStdString(){ 
			return "<AssignmentExpression></AssignmentExpression>"; 
		}
};

class Statement : public Node {
	
};

typedef std::vector<Statement*> StatementList;

class TranslationUnit : public Expression {
	public:
		StatementList statements;
		virtual std::string toStdString();
};

class DeclarationSpecifier : public Statement {
	public:
		virtual std::string toStdString();
};

typedef std::vector<DeclarationSpecifier*> DeclarationSpecifierList;

class StorageClassSpecifier : public DeclarationSpecifier {
	public:
		int token;
		std::string text;
	
		StorageClassSpecifier(int token, std::string text) 
			: token(token), text(text) { }
		virtual std::string toStdString();
};

class TypeSpecifier : public DeclarationSpecifier {
	public:
		int token;
		std::string text;
	
		TypeSpecifier(int token, std::string text) 
			: token(token), text(text) {}
		virtual std::string toStdString();
};

class TypeQualifier : public DeclarationSpecifier {
	public:
		int token;
		std::string text;
	
		TypeQualifier(int token, std::string text) 
			: token(token), text(text) {}
		virtual std::string toStdString();
};

typedef std::vector<TypeQualifier*> TypeQualifierList;

class DirectDeclarator : public Statement {
	
};

class IdentifierDeclarator : public DirectDeclarator {
	public:
		std::string identifier;
	
		IdentifierDeclarator(std::string identifier) : identifier(identifier) {}
		virtual std::string toStdString();
};

class ArrayDeclarator : public DirectDeclarator {
	public:
		DirectDeclarator *direct_declarator;
		ConstantExpression *constant_expression;
	
		ArrayDeclarator(DirectDeclarator *direct_declarator) : direct_declarator(direct_declarator) {}
		ArrayDeclarator(DirectDeclarator *direct_declarator, ConstantExpression *constant_expression) : 
			direct_declarator(direct_declarator), constant_expression(constant_expression) {}
		virtual std::string toStdString();
};

typedef std::vector<std::string*> IdentifierList;

class Declarator;

class ParameterDeclaration : public Statement {
	public:
		DeclarationSpecifierList declaration_specifiers;
		Declarator *declarator;
	
		ParameterDeclaration(DeclarationSpecifierList declaration_specifiers, Declarator *declarator) :
			declaration_specifiers(declaration_specifiers), declarator(declarator) {}
	
		ParameterDeclaration(DeclarationSpecifierList declaration_specifiers) :
			declaration_specifiers(declaration_specifiers) {}
	
		virtual std::string toStdString();
};

typedef std::vector<ParameterDeclaration*> ParameterDeclarationList;

class FunctionDeclarator : public DirectDeclarator {
	public:
		DirectDeclarator *direct_declarator;
		IdentifierList identifier_list;
		ParameterDeclarationList parameter_type_list;
	
		FunctionDeclarator(DirectDeclarator *direct_declarator) : direct_declarator(direct_declarator) {}
		FunctionDeclarator(DirectDeclarator *direct_declarator, IdentifierList identifier_list) : 
			direct_declarator(direct_declarator), identifier_list(identifier_list) {}
		FunctionDeclarator(DirectDeclarator *direct_declarator, ParameterDeclarationList parameter_type_list) : 
			direct_declarator(direct_declarator), parameter_type_list(parameter_type_list) {}
		virtual std::string toStdString();
};

class Pointer : public Statement {
	public:
		TypeQualifierList type_qualifier_list;
		Pointer *child;
	
		Pointer() {}
	
		Pointer(Pointer *child) : child(child) {}
	
		Pointer(TypeQualifierList type_qualifier_list) : type_qualifier_list(type_qualifier_list) {}
	
		Pointer(TypeQualifierList type_qualifier_list, Pointer *child) :
			child(child), type_qualifier_list(type_qualifier_list) {}
	
		virtual std::string toStdString();
};

class Declarator : public Statement {
	public:
		Pointer *pointer;
		DirectDeclarator *direct_declarator;
	
		Declarator(DirectDeclarator *direct_declarator) : direct_declarator(direct_declarator){}
		Declarator(Pointer *pointer, DirectDeclarator *direct_declarator) : 
			pointer(pointer), direct_declarator(direct_declarator){}
	
		virtual std::string toStdString();
};

class NestedDeclarator : public DirectDeclarator {
	public:
		Declarator *declarator;
	
		NestedDeclarator(Declarator *declarator) : declarator(declarator) {}
		virtual std::string toStdString();
};

class Initializer : public Statement {
	public:
		Expression *assignment_expression;
	
		Initializer(Expression *assignment_expression) :
			assignment_expression(assignment_expression) {}
		virtual std::string toStdString(){
			std::string result = "<Initializer>";
			
			if(assignment_expression != NULL){
				result += assignment_expression->toStdString();
			}
			
			result += "</Initializer>";
			
			return result;
		}
};

class InitDeclarator : public Statement {
	public:
		Declarator *declarator;
		Initializer *initializer;
	
		InitDeclarator(Declarator *declarator) : declarator(declarator) {}
		InitDeclarator(Declarator *declarator, Initializer *initializer) : 
			declarator(declarator),
			initializer(initializer) {}
	
		virtual std::string toStdString();
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
};

class ExpressionStatement : public Statement {
	public:
		ExpressionList expression_list;
	
		ExpressionStatement(ExpressionList expression_list) : 
			expression_list(expression_list) {}
	
		virtual std::string toStdString();
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
	
		JumpStatement(int token) : token(token) {}
		JumpStatement(int token, std::string identifier) : 
			token(token),
			identifier(identifier){}
	
		virtual std::string toStdString();
};

class FunctionDefinition : public Statement {
	public:
		DeclarationSpecifierList declaration_specifier_list;
		Declarator *declarator;
		DeclarationList declaration_list;
		CompoundStatement *compound_statement;
		
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
};
