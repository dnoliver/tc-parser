#include <stack>

class NBlock;

class CodeGenBlock {
public:
    //BasicBlock *block;
    //std::map<std::string, Object*> locals;
};

class CodeGenContext {
    //std::stack<CodeGenBlock *> blocks;
    //Function *mainFunction;

public:
    //Module *module;
    CodeGenContext() { /*module = new Module("main", getGlobalContext()); */}
    
    void generateCode(NBlock& root);
    //GenericValue runCode();
    //std::map<std::string, Value*>& locals() { return blocks.top()->locals; }
    //BasicBlock *currentBlock() { return blocks.top()->block; }
    //void pushBlock(BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
    //void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
};