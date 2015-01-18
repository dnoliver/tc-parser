#include <iostream>
#include <vector>

class Node {
	public:
		virtual ~Node() {}
		virtual std::string toStdString(){}
};

class Expression : public Node {
	
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

class Declarator : public Statement {
	
};

class DirectDeclarator : public Declarator {
	public:
		std::string identifier;
	
		DirectDeclarator(std::string identifier) : identifier(identifier) {}
		virtual std::string toStdString();
};

class PointerDeclarator : public Declarator {
	public:
		TypeQualifierList qualifier_list;
		PointerDeclarator *child;
	
		PointerDeclarator() {}
		PointerDeclarator(PointerDeclarator *child) : child(child) {}
		PointerDeclarator(TypeQualifierList qualifier_list) : qualifier_list(qualifier_list) {}
		PointerDeclarator(PointerDeclarator *child, TypeQualifierList qualifier_list) :
			child(child), qualifier_list(qualifier_list) {}
		virtual std::string toStdString();
};

class PointerDirectDeclarator : public Declarator {
	public:
		PointerDeclarator *pointer;
		DirectDeclarator* declarator;
	
		PointerDirectDeclarator(PointerDeclarator *pointer, DirectDeclarator* declarator) :
			pointer(pointer), declarator(declarator) {}
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

