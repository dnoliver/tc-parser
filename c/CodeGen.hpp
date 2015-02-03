#ifndef CODE_GEN_HPP
#define CODE_GEN_HPP

#include <iostream>
#include <sstream>

class CodeContext {
		unsigned int next_temp;
		unsigned int next_label;
	
	public:
		std::stringstream buffer;
	
		std::string new_temp();
		std::string new_label();
};

#endif /* CODE_GEN_HPP */