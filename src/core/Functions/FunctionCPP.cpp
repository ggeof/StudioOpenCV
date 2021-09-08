#include "FunctionCPP.h"
FunctionCPP::FunctionCPP(const char * _name) :
    name(_name)
{
    
}

FunctionCPP::~FunctionCPP() 
{
    variables.clear();
    inputs.clear();
}

std::string FunctionCPP::generatedCode() const
{
    std::string _code = "void " + std::string(name) +"(";

    for(size_t i = 0; i < this->inputs.size(); i++)
    {
        _code+=(std::string)this->inputs[i];
        if(i+1 < this->inputs.size())
            _code+="; ";
    }
    _code += "{\n";


    for(size_t i = 0; i < this->variables.size(); i++)
    {
        _code+=(std::string)this->variables[i];
        if(i+1 < this->inputs.size())
            _code+=";\n";
    }
    _code+= this->code;

    _code += "\n}\n";
    return _code;
}
