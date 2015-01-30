#include "node.hpp"

std::string Symbol::toStdString(){
	std::string result = "<Symbol>";
	
	result += "<Identifier>";
	result += identifier;
	result += "</Identifier>";
	
	//result += declarator->toStdString();
	
	result += "</Symbol>";
	return result;
}

bool SymbolTable::initialized = false;

SymbolTable* SymbolTable::instance = NULL;

SymbolTable* SymbolTable::Instance() {
	if(!initialized)
    {
        instance = new SymbolTable();
        initialized = true;
    }
    
	return instance;
}

void SymbolTable::insert(std::string identifier, Symbol* symbol){
	symbols.emplace(identifier,symbol);
}

std::string SymbolTable::toStdString(){
	std::string result = "<SymbolTable>";
	
	for (auto &symbol : symbols) {
		result += symbol.second->toStdString();
	}
	
	result += "</SymbolTable>";
	return result;
}
