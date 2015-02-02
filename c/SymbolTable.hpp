#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <iostream>

class Symbol {
	public: 
		std::string identifier;
		int invocations = 0;
	
		Symbol(std::string identifier) :
		identifier(identifier) {}
	
		std::string toStdString();
		void invoque();
};

typedef std::map<std::string,Symbol*> SymbolMap;

class SymbolTable {
	private:
		static bool initialized;
		static SymbolTable *instance;
		SymbolMap symbols;
		
		SymbolTable(){}
	public:
		~SymbolTable(){
			initialized = false;
		}
	
		static SymbolTable *Instance();
		void insert(std::string);
		bool has(std::string);
		void invoque(std::string);
		std::string toStdString();
};

#endif /* SYMBOL_TABLE_HPP */