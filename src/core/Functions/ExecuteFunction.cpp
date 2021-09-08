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
    std::string code ="#include <opencv2/core.hpp>";
    code += this->function->generatedCode();
    code += "int main() {\n";
    code += std::stri;
    code += "int main() {\n";
    code += "}\n";

    std::ofstream file("./code.cpp");

}

void ExecuteFunction::execute() const
{
    
}
