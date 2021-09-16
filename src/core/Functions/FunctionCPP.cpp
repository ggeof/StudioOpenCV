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
            _code+=", ";
    }
    _code += ")\n{\n";


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


void FunctionCPP::setCode(std::string _code)
{
	this->code = _code;
}


std::string FunctionCPP::getCode() const
{
	return this->code;
}


void FunctionCPP::setInputs(std::vector<Variable> _inputs)
{
	this->inputs = _inputs;
}


std::vector<Variable> FunctionCPP::getVariables() const
{
	return this->variables;
}


void FunctionCPP::setVariables(std::vector<Variable> _variables)
{
	this->variables = _variables;
}


std::vector<Variable> FunctionCPP::getInputs() const
{
	return this->inputs;
}
