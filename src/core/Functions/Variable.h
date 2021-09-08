#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <iostream>

struct Variable
{
    const char * name;
    const char * type;
    const char * value;

    operator std::string() const { return std::string(type) + " " + name + " = " + value + ";"; }
};

#endif // __VARIABLE_H__