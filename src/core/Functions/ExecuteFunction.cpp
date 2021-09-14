#include "ExecuteFunction.h"
#include "FunctionOpenCV.h"

#include <fstream>
#include <stdexcept>
#include <stdio.h>

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

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

    return exec("gcc code.cpp -o out.o `pkg-config opencv --cflags --libs`");
}

std::string ExecuteFunction::execute() const
{
    return exec("./out.o");
}
