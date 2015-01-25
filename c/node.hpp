#include <iostream>
#include <vector>
#include <map>

typedef std::map <std::string, std::string> PropertyList;

class XMLPrinter {
	private:
		std::string tagname;
		std::string body;
		PropertyList properties;
	
	public:
		XMLPrinter(std::string tagname) : tagname(tagname){}
		void addProperty(std::string key, std::string value) { properties[key] = value; }
		void addBody(std::string body) { this->body = body; }
		std::string getResult();
};

class Node {
	public:
		virtual ~Node() {}
		virtual std::string toStdString(){}
};

class Expression : public Node {
	
};

class ConstantExpression : public Expression {
	public:
		virtual std::string toStdString(){ return "<ConstantExpression></ConstantExpression>"; }
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

class InitDeclarator : public Statement {
	public:
		Declarator *declarator;
	
		InitDeclarator(Declarator *declarator) : declarator(declarator) {}
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
