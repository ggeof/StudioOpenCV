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

        /**
         * @brief Get the Images object
         * 
         * @return std::map<char *, cv::Mat> Image used in the function 
         */
		std::map<char *, cv::Mat> getImages() const;

        /**
         * @brief Set the Images object
         * 
         * @param _images Set the image used in the function
         */
		void setImages(std::map<char *, cv::Mat> _images);

    protected:

        /**
         * @brief toute les maps qui pourront être affiché
         * 
         */
        std::map<char *, cv::Mat> images;
};

#endif // __FUNCTIONOPENCV_H__