#include "node.hpp"
#include "ansi-c.tab.hpp"

int INDENTATION = 0;

std::string indent(std::string text){
	std::string result = "";
	for(int i = 0; i < INDENTATION; i++){
		result += "\t";
	}
	result += text;
	
	return result;
};

std::string TranslationUnit::toStdString(){
	std::string result = "<TranslationUnit>";
	
	/** Get childs std strings */
	if(statements.size() != 0){
		result += "<StatementList>";
		for ( auto &i : statements) {
			result += i->toStdString();
		}
		result += "</StatementList>";	
	}
	result += "</TranslationUnit>";
	
	return result;
}

std::string TranslationUnit::toPrettyCode(){
	std::string result = "";
	
	/** Get childs std strings */
	if(statements.size() != 0){
		int size = statements.size();
		for ( auto &i : statements) {
			result += i->toPrettyCode();
			result += --size == 0? "":"\n";
		}
	}
	
	return result;
}

std::string StorageClassSpecifier::toStdString(){
	std::string result = "<StorageClassSpecifier>" + value + "</StorageClassSpecifier>";
	return result;
}

std::string StorageClassSpecifier::toPrettyCode(){
	return value;
}

std::string TypeSpecifier::toStdString(){
	std::string result = "<TypeSpecifier>" + value + "</TypeSpecifier>";
	return result;
}

std::string TypeSpecifier::toPrettyCode(){
	return value;
}

std::string TypeQualifier::toStdString(){
	std::string result = "<TypeQualifier>" + value + "</TypeQualifier>";
	return result;
}

std::string TypeQualifier::toPrettyCode(){
	return value;
}

std::string PointerDeclarator::toStdString(){
	std::string result = "<PointerDeclarator>";
	
	if(pointer != NULL){
		result += pointer->toStdString();	
	}
	
	if(direct_declarator != NULL){
		result += direct_declarator->toStdString();	
	}
	
	result += "</PointerDeclarator>";
	
	return result;
}

std::string PointerDeclarator::toPrettyCode(){
	std::string result = "";
	
	if(pointer != NULL){
		result += pointer->toPrettyCode();	
	}
	
	if(direct_declarator != NULL){
		result += direct_declarator->toPrettyCode();	
	}
	
	return result;
}

std::string IdentifierDeclarator::toStdString(){
	std::string result = "<IdentifierDeclarator>";
		
	if(identifier != NULL){
		result += identifier->toStdString();
	}
	
	result += "</IdentifierDeclarator>";
	
	return result;
}

std::string IdentifierDeclarator::toPrettyCode(){
	return identifier->toPrettyCode();
}

std::string Identifier::toStdString(){
	std::string result = "<Identifier value='" + value + "'></Identifier>";
	return result;
}

std::string Identifier::toPrettyCode(){
	return value;
}

std::string Operator::toStdString(){
	std::string result = "<Operator value='" + value + "'></Operator>";
	return result;
}

std::string Operator::toPrettyCode(){
	return value;
}

std::string Constant::toStdString(){
	std::string result = "<Constant value='" + value + "'></Constant>";
	return result;
}

std::string Constant::toPrettyCode(){
	return value;
}

std::string StringLiteral::toStdString(){
	std::string result = "<StringLiteral value='" + value + "'></StringLiteral>";
	return result;
}

std::string StringLiteral::toPrettyCode(){
	return value;
}

std::string PrimaryExpression::toStdString(){ 
    std::string result = "<PrimaryExpression>";
	
	if(expression_list.size() != 0){
		result += "<ExpressionList>";
		for( auto &i : expression_list ){
			result += i->toStdString();
		}
		result += "</ExpressionList>";
	}
	
    result += "</PrimaryExpression>"; 

    return result;
}

std::string PrimaryExpression::toPrettyCode(){ 
    std::string result = "(";
	
	if(expression_list.size() != 0){
		for( auto &i : expression_list ){
			result += i->toPrettyCode();
		}
	}
	
    result += ")"; 

    return result;
}

std::string PostfixOperation::toStdString(){
    std::string result = "<PostfixOperation>";

    if(operand != NULL){
        result += operand->toStdString();
    }
	
	if(unary_operator != NULL){
		result += unary_operator->toStdString();
	}

    result += "</PostfixOperation>";
    return result;
}

std::string PostfixOperation::toPrettyCode(){
    std::string result = "";

    if(operand != NULL){
        result += operand->toPrettyCode();
    }
	
	if(unary_operator != NULL){
		result += unary_operator->toPrettyCode();
	}
    return result;
}

std::string ArrayAccess::toStdString(){
	std::string result = "<ArrayAccess>";
	
	if(postfix_expression != NULL){
		result += postfix_expression->toStdString();
	}
	
	if(expression.size() != 0){
		result += "<ExpressionList>";
		for( auto &i : expression){
			result += i->toStdString();
		}
		result += "</ExpressionList>";
	}
	
	result += "</ArrayAccess>";
	return result;
}

std::string ArrayAccess::toPrettyCode(){
	std::string result = "";
	
	if(postfix_expression != NULL){
		result += postfix_expression->toPrettyCode();
	}
	
	if(expression.size() != 0){
		result += "[";
		for( auto &i : expression){
			result += i->toPrettyCode();
		}
		result += "]";
	} else {
		result += "[]";
	}
	
	return result;
}

std::string FunctionCall::toStdString(){
  std::string result = "<FunctionCall>";

  if(postifx_expression != NULL){
      result += postifx_expression->toStdString();
  }
  
  if(argument_expression_list.size() != 0){
	  result += "<ArgumentExpressionList>";
	  for( auto &i : argument_expression_list){
		  result += i->toStdString();
	  }
	  result += "</ArgumentExpressionList>";
  }

  result += "</FunctionCall>";
  return result;
}

std::string FunctionCall::toPrettyCode(){
	std::string result = "";

	if(postifx_expression != NULL){
		result += postifx_expression->toPrettyCode();
	}

	if(argument_expression_list.size() != 0){
	  result += "(";
	  for( auto &i : argument_expression_list){
		  result += i->toPrettyCode();
	  }
	  result += ")";
	}
	else {
		result += "()";
	}

	return result;
}

std::string UnaryOperation::toStdString(){
    std::string result = "<UnaryOperation>";

	if(unary_operator != NULL){
		result += unary_operator->toStdString();
	}
	
    if(operand != NULL){
        result += operand->toStdString();
    }

    result += "</UnaryOperation>";
    return result;
}

std::string UnaryOperation::toPrettyCode(){
    std::string result = "";

	if(unary_operator != NULL){
		result += unary_operator->toPrettyCode();
	}
	
    if(operand != NULL){
        result += operand->toPrettyCode();
    }

    return result;
}

std::string BinaryOperation::toStdString(){
    std::string result = "<BinaryOperation>";

    if(left_operand != NULL){
        result += left_operand->toStdString();
    }
	
	if(binary_operator != NULL){
		result += binary_operator->toStdString();
	}

    if(right_operand != NULL){
        result += right_operand->toStdString();
    }

    result += "</BinaryOperation>";
    return result;
}

std::string BinaryOperation::toPrettyCode(){
    std::string result = "";

    if(left_operand != NULL){
        result += left_operand->toPrettyCode();
    }
	
	if(binary_operator != NULL){
		result += " ";
		result += binary_operator->toPrettyCode();
	}

    if(right_operand != NULL){
		result += " ";
        result += right_operand->toPrettyCode();
    }

    return result;
}

std::string ConditionalExpression::toStdString(){
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

std::string ConditionalExpression::toPrettyCode(){
    std::string result = "";

    if(logical_or_expression != NULL){
        result += logical_or_expression->toPrettyCode();
		result += " ?";
    }

    if(expression.size() != 0){
        result += " ";
        for( auto &i : expression ) {
            result += i->toPrettyCode();
        }
        result += " :";	
    }

    if(conditional_expression != NULL){
		result += " ";
        result += conditional_expression->toPrettyCode();
    }
	
    return result;
}

std::string AssignmentExpression::toStdString(){
  std::string result = "<AssignmentExpression>";
  
  if(unary_expression != NULL){
    result += unary_expression->toStdString();
  }
  
  if(assignment_operator != NULL){
    result += assignment_operator->toStdString();
  }
  
  if(assignment_expression != NULL){
    result += assignment_expression->toStdString();
  }
  
  result += "</AssignmentExpression>"; 
  return result;
}

std::string AssignmentExpression::toPrettyCode(){
	std::string result = "";

	if(unary_expression != NULL){
		result += unary_expression->toPrettyCode();
	}

	if(assignment_operator != NULL){
		result += " ";
		result += assignment_operator->toPrettyCode();
	}

	if(assignment_expression != NULL){
		result += " ";
		result += assignment_expression->toPrettyCode();
	}

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

std::string ArrayDeclarator::toPrettyCode(){
	std::string result = "";
	
	if(direct_declarator != NULL){
		result += direct_declarator->toPrettyCode();	
	}
	
	result += "[";
	
	if(constant_expression != NULL){
		result += constant_expression->toPrettyCode();	
	}
	
	result += "]";
	
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
		for ( auto &i : identifier_list) {
			result += i->toStdString();
		}
		result += "</IdentifierList>";	
	}
	
	if(parameter_type_list.size() != 0){
		result += "<ParameterDeclarationList>";
		for ( auto &i : parameter_type_list) {
			result += i->toStdString();
		}
		result += "</ParameterDeclarationList>";	
	}
	
	result += "</FunctionDeclarator>";
	return result;
}

std::string FunctionDeclarator::toPrettyCode(){
	std::string result = "";
	
	if(direct_declarator != NULL){
		result += direct_declarator->toPrettyCode();	
	}
	
	result += "(";
	if(parameter_type_list.size() != 0){
		int size = parameter_type_list.size();
		for ( auto &i : parameter_type_list) {
			result += i->toPrettyCode();
			result += --size == 0? "":", ";
		}
	}
	
	/** Get specifiers childs std strings */
	if(identifier_list.size() != 0) {
		for ( auto &i : identifier_list) {
			result += i->toPrettyCode();
		}
	}
	result += ")";
	
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

std::string NestedDeclarator::toPrettyCode(){
	std::string result = "(";
	
	if(declarator != NULL){
		result += declarator->toPrettyCode();	
	}
	
	result += ")";
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
		for ( auto &i : type_qualifier_list) {
			result += i->toStdString();
		}
		result += "</TypeQualifierList>";	
	}
	
	result += "</Pointer>";
	
	return result;
}

std::string Pointer::toPrettyCode(){
	std::string result = "*";
	
	if(child){
		result += child->toPrettyCode();
	}
	
	/** Get specifiers childs std strings */
	if(type_qualifier_list.size() != 0){
		for ( auto &i : type_qualifier_list) {
			result += i->toPrettyCode();
		}
	}
	
	return result;
}

std::string InitDeclarator::toStdString(){
	std::string result = "<InitDeclarator>";
	
	if(declarator != NULL){
		result += declarator->toStdString();	
	}
	
	if(initializer != NULL){
		result += initializer->toStdString();	
	}
	
	result += "</InitDeclarator>";
	
	return result;
}

std::string InitDeclarator::toPrettyCode(){
	std::string result = "";
	
	if(declarator != NULL){
		result += declarator->toPrettyCode();	
	}
	
	if(initializer != NULL){
		result += " = ";
		result += initializer->toPrettyCode();	
	}
	
	return result;
}

std::string Initializer::toStdString(){
    std::string result = "<Initializer>";

    if(assignment_expression != NULL){
        result += assignment_expression->toStdString();
    }

    result += "</Initializer>";

    return result;
}

std::string Initializer::toPrettyCode(){
    std::string result = "";

    if(assignment_expression != NULL){
        result += assignment_expression->toPrettyCode();
    }

    return result;
}

std::string Declaration::toStdString(){
	std::string result = "<Declaration>";	
	
	/** Get specifiers childs std strings */
	if(specifiers.size() != 0 ){
		result += "<DeclarationSpecifierList>";
		for ( auto &i : specifiers ) {
			result += i->toStdString();
		}
		result += "</DeclarationSpecifierList>";	
	}
	
	/** Get specifiers childs std strings */
	if(declarators.size() != 0){
		result += "<InitDeclaratorList>";
		for( auto &i : declarators ) {
			result += i->toStdString();
		}
		result += "</InitDeclaratorList>";	
	}
	
	result += "</Declaration>";
	
	return result;
}

std::string Declaration::toPrettyCode(){
	std::string result = "";	
	
	/** Get specifiers childs std strings */
	if(specifiers.size() != 0 ){
		int size = specifiers.size();
		for ( auto &i : specifiers ) {
			result += i->toPrettyCode();
			result += --size == 0? "":" ";
		}
	}
	
	/** Get specifiers childs std stringqs */
	if(declarators.size() != 0){
		result += " ";
		int size = declarators.size();
		for( auto &i : declarators ) {
			result += i->toPrettyCode();
			result += --size == 0? "":", ";
		}
	}
	
	result += ";";
	
	return result;
};

std::string ParameterDeclaration::toStdString(){
	std::string result = "<ParameterDeclaration>";	
	
	/** Get specifiers childs std strings */
	if(declaration_specifiers.size() != 0 ){
		result += "<DeclarationSpecifierList>";
		for( auto &i : declaration_specifiers ) {
			result += i->toStdString();
		}
		result += "</DeclarationSpecifierList>";	
	}
	
	if(declarator != NULL){
		result += declarator->toStdString();
	}
	
	result += "</ParameterDeclaration>";
	
	return result;
}

std::string ParameterDeclaration::toPrettyCode(){
	std::string result = "";	
	
	/** Get specifiers childs std strings */
	if(declaration_specifiers.size() != 0 ){
		int size = declaration_specifiers.size();
		for( auto &i : declaration_specifiers ) {
			result += i->toPrettyCode();
			result += --size == 0? "" : " ";
		}
	}
	
	if(declarator != NULL){
		result += " ";
		result += declarator->toPrettyCode();
	}
	
	return result;
}

std::string CaseStatement::toStdString(){
	std::string result = "<CaseStatement>";
	
	if(constant_expression != NULL){
		result += constant_expression->toStdString();
	}
	
	if(statement != NULL){
		result += statement->toStdString();
	}
	
	result += "</CaseStatement>";
	return result;
}

std::string CaseStatement::toPrettyCode(){
	std::string result = "case";
	
	if(constant_expression != NULL){
		result += " ";
		result += constant_expression->toPrettyCode();
		result += ":";
	}
	
	if(statement != NULL){
		result += " ";
		result += statement->toPrettyCode();
	}
	
	return result;
}

std::string DefaultStatement::toStdString(){
	std::string result = "<DefaultStatement>";
	
	if(statement != NULL){
		result += statement->toStdString();
	}
	
	result += "</DefaultStatement>";
	return result;
}

std::string DefaultStatement::toPrettyCode(){
	std::string result = "default:";

	if(statement != NULL){
		result += " ";
		result += statement->toPrettyCode();
	}
	
	return result;
}

std::string TaggedStatement::toStdString(){
	std::string result = "<TaggedStatement>";
	
	if(identifier_declarator != NULL){
		result += identifier_declarator->toStdString();
	}
	
	if(statement != NULL){
		result += statement->toStdString();
	}
	
	result += "</TaggedStatement>";
	return result;
}

std::string TaggedStatement::toPrettyCode(){
	std::string result = "";

	if(identifier_declarator != NULL){
		result += identifier_declarator->toPrettyCode();
		result += ":";
	}
	
	if(statement != NULL){
		result += " ";
		result += statement->toPrettyCode();
	}
	
	return result;
}


std::string CompoundStatement::toStdString(){
	std::string result = "<CompoundStatement>";
	
    if(declaration_list.size() != 0){
		result += "<DeclarationList>";
		for( auto &i : declaration_list ) {
			result += i->toStdString();
		}
		result += "</DeclarationList>";	
	}
  
	if(statement_list.size() != 0){
		result += "<StatementList>";
		for( auto &i : statement_list ) {
			result += i->toStdString();
		}
		result += "</StatementList>";	
	}
	
	result += "</CompoundStatement>";
	return result;
}

std::string CompoundStatement::toPrettyCode(){
	std::string result = "{";
	INDENTATION++;
	
    if(declaration_list.size() != 0){
		result += "\n";
		int size = declaration_list.size();
		for( auto &i : declaration_list ) {
			result += indent(i->toPrettyCode());
			result += "\n"; 
		}
	}
  
	if(statement_list.size() != 0){
		result += "\n";
		int size = statement_list.size();
		for( auto &i : statement_list ) {
			result += indent(i->toPrettyCode());
			result += "\n";
		}
	}
	
	INDENTATION--;
	result += "}";
	return result;
}

std::string ExpressionStatement::toStdString(){
	std::string result = "<ExpressionStatement>";
	
	if(expression_list.size() != 0){
		result += "<ExpressionList>";
		for( auto &i : expression_list ) {
			result += i->toStdString();
		}
		result += "</ExpressionList>";	
	}
	result += "</ExpressionStatement>";
	return result;
}

std::string ExpressionStatement::toPrettyCode(){
	std::string result = "";
	
	if(expression_list.size() != 0){
		for( auto &i : expression_list ) {
			result += i->toPrettyCode();
		}	
	}
	result += ";";
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
	std::string result = "<JumpStatement token='" + std::to_string(token) + "'";

	if(token == GOTO){
		result += " identifier='" + identifier + "'";
	}

	result += ">";

	if(expression_list.size() != 0){
		result += "<ExpressionList>";
		for(auto &i : expression_list){
			result += i->toStdString();
		}
		result += "</ExpressionList>";
	}

	result += "</JumpStatement>";
	return result;
}

std::string JumpStatement::toPrettyCode(){
	std::string result = "";

	if(token == GOTO){
		result += "goto ";
		result += identifier;
		result += ";";
	}
	
	if(token == CONTINUE){
		result += "continue;";
	}
	
	if(token == BREAK){
		result += "break;";
	}
	
	if(token == RETURN){
		result += "return";
		if(expression_list.size() != 0){
			result += " ";
			for(auto &i : expression_list){
				result += i->toPrettyCode();
			}
		}
		result += ";";
	}

	return result;
}

std::string FunctionDefinition::toStdString(){
	std::string result = "<FunctionDefinition>";
	
	if(declaration_specifier_list.size() != 0){
		result += "<DeclarationSpecifierList>";
		for( auto &i : declaration_specifier_list ) {
			result += i->toStdString();
		}
		result += "</DeclarationSpecifierList>";	
	}
	
	if(declarator != NULL){
		result += declarator->toStdString();	
	}
	
	if(declaration_list.size() != 0){
		result += "<DeclarationList>";
		for( auto &i : declaration_list ) {
			result += i->toStdString();
		}
		result += "</DeclarationList>";	
	}

	if(compound_statement != NULL){
		result += compound_statement->toStdString();	
	}
	
	result += "</FunctionDefinition>";
	return result;
}

std::string FunctionDefinition::toPrettyCode(){
	std::string result = "";
	
	if(declaration_specifier_list.size() != 0){
		for( auto &i : declaration_specifier_list ) {
			result += i->toPrettyCode();
		}	
	}
	
	if(declarator != NULL){
		result += " ";
		result += declarator->toPrettyCode();	
	}
	
	if(declaration_list.size() != 0){
		for( auto &i : declaration_list ) {
			result += i->toPrettyCode();
		}	
	}

	if(compound_statement != NULL){
		result += compound_statement->toPrettyCode();	
	}
	
	return result;
}