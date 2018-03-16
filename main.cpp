#include <iostream>

#include "Str.h"

int main()
{
    Str defaultStr;
    Str argStr(5, 'a');
    Str nullTermCharArrayStr("hello");
    Str iteratorStr(argStr.begin(), argStr.end());

    for (size_t i = 0; i != argStr.size(); ++i)
        std::cout << argStr[i] << " ";
    std::cout << std::endl;

    for (size_t i = 0; i != nullTermCharArrayStr.size(); ++i)
        std::cout << nullTermCharArrayStr[i] << " ";
    std::cout << std::endl;

    for (size_t i = 0; i != iteratorStr.size(); ++i)
        std::cout << iteratorStr[i] << " ";
    std::cout << std::endl;
}
