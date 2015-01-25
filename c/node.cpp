#include "node.hpp"
#include "ansi-c.tab.hpp"

std::string XMLPrinter::getResult(){
	std::string result = "<" + tagname;
	
	for (PropertyList::iterator i = properties.begin(); i != properties.end(); ++i) {
    	result += i->first + "=" + i->second;
    }
	result += ">";
	result += body;
	result += "</" + tagname + ">";
	
	return result;
}

std::string TranslationUnit::toStdString(){
	XMLPrinter printer("TranslationUnit");
	std::string body = "";
	
	/** Get childs std strings */
	if(statements.size() != 0){
		body += "<StatementList>";
		StatementList::const_iterator it;
		for (it = statements.begin(); it != statements.end(); it++) {
			body += (**it).toStdString();
		}
		body += "</StatementList>";	
	}
	
	printer.addBody(body);
	
	return printer.getResult();
}

std::string DeclarationSpecifier::toStdString(){
	return "<DeclarationSpecifier></DeclarationSpecifier>";
}

std::string StorageClassSpecifier::toStdString(){
	std::string result = "<StorageClassSpecifier text='" + text + "'></StorageClassSpecifier>";
	
	return result;
}

std::string TypeSpecifier::toStdString(){
	std::string result = "<TypeSpecifier text='" + text + "'></TypeSpecifier>";
	return result;
}

std::string TypeQualifier::toStdString(){
	std::string result = "<TypeQualifier text='" + text + "'></TypeQualifier>";
	return result;
}

std::string Declarator::toStdString(){
	std::string result = "<Declarator>";
	
	if(pointer != NULL){
		result += pointer->toStdString();	
	}
	
	if(direct_declarator != NULL){
		result += direct_declarator->toStdString();	
	}
	
	result += "</Declarator>";
	
	return result;
}

std::string IdentifierDeclarator::toStdString(){
	std::string result = "<IdentifierDeclarator identifier='" + identifier + "'></IdentifierDeclarator>";
	
	return result;
}

std::string ArrayDeclarator::toStdString(){
	std::string result = "<ArrayDeclarator>";
	
	if(direct_declarator != NULL){
		result += direct_declarator->toStdString();	
	}
	
	if(constant_expression != NULL){
		result += constant_expression->toStdString();	
	}
	
	result += "</ArrayDeclarator>";
	return result;
}

std::string FunctionDeclarator::toStdString(){
	std::string result = "<FunctionDeclarator>";
	
	if(direct_declarator != NULL){
		result += direct_declarator->toStdString();	
	}
	
	/** Get specifiers childs std strings */
	if(identifier_list.size() != 0) {
		result += "<IdentifierList>";
		IdentifierList::const_iterator it_1;
		for (it_1 = identifier_list.begin(); it_1 != identifier_list.end(); it_1++) {
			result += (**it_1);
		}
		result += "</IdentifierList>";	
	}
	
	if(parameter_type_list.size() != 0){
		result += "<ParameterDeclarationList>";
		ParameterDeclarationList::const_iterator it_2;
		for (it_2 = parameter_type_list.begin(); it_2 != parameter_type_list.end(); it_2++) {
			result += (**it_2).toStdString();
		}
		result += "</ParameterDeclarationList>";	
	}
	
	result += "</FunctionDeclarator>";
	return result;
}

std::string NestedDeclarator::toStdString(){
	std::string result = "<NestedDeclarator>";
	
	if(declarator != NULL){
		result += declarator->toStdString();	
	}
	
	result += "</NestedDeclarator>";
	return result;
}

std::string Pointer::toStdString(){
	std::string result = "<Pointer>";
	
	if(child){
		result += child->toStdString();
	}
	
	/** Get specifiers childs std strings */
	if(type_qualifier_list.size() != 0){
		result += "<TypeQualifierList>";
		TypeQualifierList::const_iterator it_1;
		for (it_1 = type_qualifier_list.begin(); it_1 != type_qualifier_list.end(); it_1++) {
			result += (**it_1).toStdString();
		}
		result += "</TypeQualifierList>";	
	}
	
	result += "</Pointer>";
	
	return result;
}

std::string InitDeclarator::toStdString(){
	std::string result = "<InitDeclarator>";
	result += declarator->toStdString();
	result += "</InitDeclarator>";
	
	return result;
}

std::string Declaration::toStdString(){
	std::string result = "<Declaration>";	
	
	/** Get specifiers childs std strings */
	if(specifiers.size() != 0 ){
		result += "<DeclarationSpecifierList>";
		DeclarationSpecifierList::const_iterator it_1;
		for (it_1 = specifiers.begin(); it_1 != specifiers.end(); it_1++) {
			result += (**it_1).toStdString();
		}
		result += "</DeclarationSpecifierList>";	
	}
	
	/** Get specifiers childs std strings */
	if(declarators.size() != 0){
		result += "<InitDeclaratorList>";
		InitDeclaratorList::const_iterator it_2;
		for (it_2 = declarators.begin(); it_2 != declarators.end(); it_2++) {
			result += (**it_2).toStdString();
		}
		result += "</InitDeclaratorList>";	
	}
	
	result += "</Declaration>";
	
	return result;
}

std::string ParameterDeclaration::toStdString(){
	std::string result = "<ParameterDeclaration>";	
	
	/** Get specifiers childs std strings */
	if(declaration_specifiers.size() != 0 ){
		result += "<DeclarationSpecifierList>";
		DeclarationSpecifierList::const_iterator it_1;
		for (it_1 = declaration_specifiers.begin(); it_1 != declaration_specifiers.end(); it_1++) {
			result += (**it_1).toStdString();
		}
		result += "</DeclarationSpecifierList>";	
	}
	
	/** Get specifiers childs std strings */
	if(declarator != NULL){
		result += declarator->toStdString();
	}
	
	result += "</ParameterDeclaration>";
	
	return result;
}

std::string LabeledStatement::toStdString(){
	std::string result = "<LabeledStatement>";
	result += "</LabeledStatement>";
	return result;
}

std::string CompoundStatement::toStdString(){
	std::string result = "<CompoundStatement>";
	
	if(statement_list.size() != 0){
		result += "<StatementList>";
		StatementList::const_iterator it_1;
		for (it_1 = statement_list.begin(); it_1 != statement_list.end(); it_1++) {
			result += (**it_1).toStdString();
		}
		result += "</StatementList>";	
	}
	
	if(declaration_list.size() != 0){
		result += "<StatementList>";
		DeclarationList::const_iterator it_2;
		for (it_2 = declaration_list.begin(); it_2 != declaration_list.end(); it_2++) {
			result += (**it_2).toStdString();
		}
		result += "</StatementList>";	
	}
	
	result += "</CompoundStatement>";
	return result;
}

std::string ExpressionStatement::toStdString(){
	std::string result = "<ExpressionStatement>";
	result += "</ExpressionStatement>";
	return result;
}

std::string SelectionStatement::toStdString(){
	std::string result = "<SelectionStatement>";
	result += "</SelectionStatement>";
	return result;
}

std::string IterationStatement::toStdString(){
	std::string result = "<IterationStatement>";
	result += "</IterationStatement>";
	return result;
}

std::string JumpStatement::toStdString(){
	std::string result = "<JumpStatement>";
	result += "</JumpStatement>";
	return result;
}

std::string FunctionDefinition::toStdString(){
	std::string result = "<FunctionDefinition>";
	
	if(declaration_specifier_list.size() != 0){
		result += "<DeclarationSpecifierList>";
		DeclarationSpecifierList::const_iterator it;
		for(it = declaration_specifier_list.begin(); it != declaration_specifier_list.end(); it++){
			result += (**it).toStdString();
		}
		result += "</DeclarationSpecifierList>";	
	}
	
	if(declarator != NULL){
		result += declarator->toStdString();	
	}
	
	if(declaration_list.size() != 0){
		result += "<DeclarationList>";
		DeclarationList::const_iterator it_2;
		for(it_2 = declaration_list.begin(); it_2 != declaration_list.end(); it_2++){
			result += (**it_2).toStdString();
		}
		result += "</DeclarationList>";	
	}

	if(compound_statement != NULL){
		result += compound_statement->toStdString();	
	}
	
	result += "</FunctionDefinition>";
	return result;
}