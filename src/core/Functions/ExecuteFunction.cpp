#include "ExecuteFunction.h"
#include "FunctionOpenCV.h"

#include <fstream>

ExecuteFunction::ExecuteFunction(std::shared_ptr<FunctionCPP> _function) :
    function(_function)
{
    
}

ExecuteFunction::~ExecuteFunction() 
{
    
}

std::string ExecuteFunction::compile() 
{
    std::string code ="#include <opencv2/core.hpp>\n";
    code += this->function->generatedCode() + "\n";
    code += "int main() {\n";
    code += std::string(this->function->getName())+"();";
    code += "return 1;\n";
    code += "}\n";

    std::ofstream file("./code.cpp");
    file << code;
    file.close();

    system("gcc code.cpp -o out.o `pkg-config opencv --cflags --libs`");

    return "TODO";
}

void ExecuteFunction::execute() const
{
    system("./out.o");
}
