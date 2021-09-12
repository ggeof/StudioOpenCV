#ifndef __EXECUTEFUNCTION_H__
#define __EXECUTEFUNCTION_H__

#include <string>
#include <memory>
#include "FunctionCPP.h"

class ExecuteFunction
{
public:
    /**
     * @brief Construct a new Execute Function object
     * 
     * @param function qui sera compiler/executer
     */
    ExecuteFunction(std::shared_ptr<FunctionCPP> function);
    
    /**
     * @brief Destroy the Execute Function object
     * 
     */
    ~ExecuteFunction();

    /**
     * @brief Compile the function 
     * 
     * @return std::string return of the compilation
     */
    std::string compile();

    /**
     * @brief Execute the function
     */
    void execute() const;

protected:

    /**
     * @brief Function
     * 
     */
    std::shared_ptr<FunctionCPP> function;
};

#endif // __EXECUTEFUNCTION_H__