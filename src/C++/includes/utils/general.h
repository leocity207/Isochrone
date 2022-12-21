#ifndef GENERAL_H
#define GENERAL_H

#include <string_view>
#include <optional>


namespace Generals
{
    std::string_view Trim_Space_Front_Back(const std::string_view& str);
    std::string&& Trim_Space_Front_Back(std::string&& str);
    double Parse_Angle(const std::string_view& str);
}

#endif //GENERAL_H
