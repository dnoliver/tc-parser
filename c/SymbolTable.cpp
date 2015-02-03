#include "SymbolTable.hpp"

std::string Symbol::toStdString(){
	std::string result = "<Symbol>";
	result += "<Identifier>" + identifier + "</Identifier>";
	result += "<Invocations>" + std::to_string(invocations) + "</Invocations>";
	result += "</Symbol>";
	return result;
}

void Symbol::invoque(){
	invocations++;
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

bool SymbolTable::has(std::string identifier){
	return symbols.find(identifier) != symbols.end();
}

void SymbolTable::invoque(std::string identifier){
	SymbolMap::iterator i = symbols.find(identifier);
	
	if( i != symbols.end()){
		i->second->invoque();
	}
	else {
		// throw exceptions
	}
}


std::string SymbolTable::toStdString(){
	std::string result = "<SymbolTable>";
	
	for (auto &symbol : symbols) {
		result += symbol.second->toStdString();
	}
	
	result += "</SymbolTable>";
	return result;
}
