#ifndef __FUNCTIONCPP_H__
#define __FUNCTIONCPP_H__

#include <iostream>
#include <vector>

#include "Variable.h"

// TODO : Sauvegarde
// TODO : sortie

class FunctionCPP
{
    public:
        /**
         * @brief Construct a new Function CPP object
         * 
         * @param name of the function
         */
        FunctionCPP(const char * name);

        /**
         * @brief Destroy the Function CPP object
         */
        ~FunctionCPP();

        /**
         * @brief Génère le code CPP de la fonction
         * 
         * @return std::string Code généré
         */
        virtual std::string generatedCode() const;


    protected:

        /**
         * @brief Name of the function
         * 
         */
        const char * name;

        /**
         * @brief Code of the function
         * 
         */
        std::string code;

        /**
         * @brief Inputs of the function
         * 
         */
        std::vector<Variable> inputs;

        /**
         * @brief Variables of the function
         * 
         */
        std::vector<Variable> variables;


};


#endif // __FUNCTIONCPP_H__