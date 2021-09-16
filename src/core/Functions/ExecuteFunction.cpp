#include "ExecuteFunction.h"
#include "FunctionOpenCV.h"

#include <fstream>
#include <stdexcept>
#include <stdio.h>

std::string exec(const char* cmd) {
    const static std::string FILE_OUTPUT = "output.cmd";
    system((std::string(cmd) + " > " + FILE_OUTPUT +  " 2> " + FILE_OUTPUT).c_str());

    std::ifstream ifs(FILE_OUTPUT);
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    std::remove(FILE_OUTPUT.c_str());

    return ret;
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
    std::string code ="#include <opencv2/core.hpp>\n#include <iostream>\n";
    code += this->function->generatedCode() + "\n";
    code += "int main() {\n";
    code += std::string(this->function->getName())+"();";
    code += "return 1;\n";
    code += "}\n";

    std::ofstream file("./code.cpp");
    file << code;
    file.close();

    return exec("g++ code.cpp -o out.o `pkg-config opencv --cflags --libs`");
}

std::string ExecuteFunction::execute() const
{
    return exec("./out.o");
}
