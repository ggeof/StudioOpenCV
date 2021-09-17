#include "FunctionOpenCV.h"


FunctionOpenCV::FunctionOpenCV(const char * name)  :
    FunctionCPP(name)
{
    
}

FunctionOpenCV::~FunctionOpenCV() 
{
    this->images.clear();
}

std::string FunctionOpenCV::generatedCode() const
{
    std::string _code = FunctionCPP::generatedCode();

    std::string declaration = "";
    std::string saves = "\n";

    for(auto it = this->images.begin(); it != this->images.end(); it++)
    {
        declaration+= std::string("cv::Mat ")+it->first+";\n";
        saves+= std::string("cv::imwrite("+it->first+", \"./saveMat/")+it->first+".png\");\n";
    }

    _code.insert(_code.find_first_of("{")+2, declaration);
    _code.insert(_code.find_last_of("}")-1, saves);

    //std::cout << _code;
    return _code;
}


std::map<std::string, cv::Mat> FunctionOpenCV::getImages() const
{
	return this->images;
}


void FunctionOpenCV::setImages(std::map<std::string, cv::Mat> _images)
{
	this->images = _images;
}
