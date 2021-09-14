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

        /**
         * @brief Get the Name object
         * 
         * @return const char* Name of the function
         */
        inline const char * getName() { return this->name; }

        /**
         * @brief Set the Code object
         * 
         * @param _code New code for the function
         */
		void setCode(std::string _code);

        /**
         * @brief Set the Inputs object
         * 
         * @param _inputs New Parameters for the function
         */
		void setInputs(std::vector<Variable> _inputs);

        /**
         * @brief Set the Variables object
         * 
         * @param _variables New variable for the function
         */
		void setVariables(std::vector<Variable> _variables);


        /**
         * @brief Get the Code object
         * 
         * @return std::string Code of the function
         */
		std::string getCode() const;

        /**
         * @brief Get the Inputs object
         * 
         * @return std::vector<Variable> Input of the function 
         */
		std::vector<Variable> getInputs() const;

        /**
         * @brief Get the Variables object
         * 
         * @return std::vector<Variable> Variables of the function
         */
		std::vector<Variable> getVariables() const;

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