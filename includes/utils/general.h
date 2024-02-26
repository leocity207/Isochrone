#ifndef GENERAL_H
#define GENERAL_H

// STL
#include <string_view>
#include <vector>


namespace Generals
{
    std::string_view Trim_Space_Front_Back(const std::string_view& str);
    std::string&& Trim_Space_Front_Back(std::string&& str);
    double Parse_Angle(const std::string_view& str);

    template<class T>
    std::vector<std::vector<T>> Transpose(const std::vector<std::vector<T>>& matrix);
}

#include "general.hpp"

#endif //GENERAL_H
