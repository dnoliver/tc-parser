#include "node.hpp"
#include "ansi-c.tab.hpp"

std::string TranslationUnit::toStdString(){
	std::string result = "<TranslationUnit>";
	
	/** Get childs std strings */
	result += "<StatementList>";
	StatementList::const_iterator it;
	for (it = statements.begin(); it != statements.end(); it++) {
        result += (**it).toStdString();
	}
	result += "</StatementList>";
	result += "</TranslationUnit>";
	
	return result;
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

std::string DirectDeclarator::toStdString(){
	std::string result = "<DirectDeclarator identifier='" + identifier + "'></DirectDeclarator>";
	
	return result;
}

std::string PointerDeclarator::toStdString(){
	std::string result = "<PointerDeclarator>";
	if(child){
		result += child->toStdString();
	}
	result += "</PointerDeclarator>";
	
	return result;
}

std::string PointerDirectDeclarator::toStdString(){
	std::string result = "<PointerDirectDeclarator>";
	result += pointer->toStdString();
	result += declarator->toStdString();
	result += "</PointerDirectDeclarator>";
	
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
	result += "<DeclarationSpecifierList>";
	DeclarationSpecifierList::const_iterator it_1;
	for (it_1 = specifiers.begin(); it_1 != specifiers.end(); it_1++) {
        result += (**it_1).toStdString();
	}
	result += "</DeclarationSpecifierList>";
	
	/** Get specifiers childs std strings */
	result += "<InitDeclaratorList>";
	InitDeclaratorList::const_iterator it_2;
	for (it_2 = declarators.begin(); it_2 != declarators.end(); it_2++) {
        result += (**it_2).toStdString();
	}
	result += "</InitDeclaratorList>";
	
	result += "</Declaration>";
	
	return result;
}
