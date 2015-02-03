#include "CodeGen.hpp"

std::string CodeContext::new_temp(){
	return "t" + std::to_string(next_temp++);
}

std::string CodeContext::new_label(){
	return "L" + std::to_string(next_label++);
}