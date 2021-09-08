#ifndef __EXECUTEFUNCTION_H__
#define __EXECUTEFUNCTION_H__

#include <string>
#include <memory>
#include "FunctionCPP.h"

class ExecuteFunction
{
public:
    ExecuteFunction(std::shared_ptr<FunctionCPP> function);
    ~ExecuteFunction();

    std::string compile();

    void execute() const;

protected:
    std::shared_ptr<FunctionCPP> function;

    std::string fileCompiled;
};

#endif // __EXECUTEFUNCTION_H__