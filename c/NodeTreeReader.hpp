#include <iostream>

class NodeTreeReader {
	private:
	
	public:
};

class NodeWritter {
	protected:
		std::string result;
	
	public:
		virtual std::string getResult() { return result; }
};

class XMLPrinter : public NodeWriter {
		std::string tagname;
		std::string body;
		std::map <std::string, std::string> properties;
	
	public:
		XMLPrinter(std::string tagname) : tagname(tagname){}
		void addProperty(std::string key, std::string value) { properties[key] = value; }
		void addBody(std::string body) { this->body = body; }
};

class PrettyPrinter : public NodeWriter {
	
};

class ThreeWayCodePrinter : public NodeWriter {
	
};

