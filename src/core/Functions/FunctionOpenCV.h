#ifndef __FUNCTIONOPENCV_H__
#define __FUNCTIONOPENCV_H__

#include <opencv2/core.hpp>
#include <map>

#include "FunctionCPP.h"

class FunctionOpenCV : public FunctionCPP
{
    public:
        /**
         * @brief Construct a new Function CPP object
         * 
         * @param name of the function
         */
        FunctionOpenCV(const char * name);

        /**
         * @brief Destroy the Function CPP object
         */
        ~FunctionOpenCV();

        /**
         * @brief Génère le code CPP de la fonction
         * 
         * @return std::string Code généré
         */
        virtual std::string generatedCode() const;

    protected:

        /**
         * @brief toute les maps qui pourront être affiché
         * 
         */
        std::map<char *, cv::Mat> images;
};

#endif // __FUNCTIONOPENCV_H__