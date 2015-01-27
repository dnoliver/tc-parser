#include "node.hpp"
#include "ansi-c.tab.hpp"

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

std::string Identifier::toStdString(){
	std::string result = "<Identifier value='" + value + "'></Identifier>";
	return result;
}

std::string Operator::toStdString(){
	std::string result = "<Operator value='" + value + "'></Operator>";
	return result;
}

std::string Constant::toStdString(){
	std::string result = "<Constant value='" + value + "'></Constant>";
	return result;
}

std::string StringLiteral::toStdString(){
	std::string result = "<StringLiteral value='" + value + "'></StringLiteral>";
	return result;
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
		for ( auto &i : type_qualifier_list) {
			result += i->toStdString();
		}
		result += "</TypeQualifierList>";	
	}
	
	result += "</Pointer>";
	
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

std::string Initializer::toStdString(){
    std::string result = "<Initializer>";

    if(assignment_expression != NULL){
        result += assignment_expression->toStdString();
    }

    result += "</Initializer>";

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

std::string LabeledStatement::toStdString(){
	std::string result = "<LabeledStatement>";
	result += "</LabeledStatement>";
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

	result += "</JumpStatement>";
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