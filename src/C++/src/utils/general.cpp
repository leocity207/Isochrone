#include "includes/utils/general.h"
#include "includes/utils/exception_def.h"

#include <algorithm>
#include <cctype>
#include <ranges>

namespace Generals
{
        
    std::string_view Trim_Space_Front_Back(const std::string_view& str)
    {
        // Trim leading and trailing whitespace
        size_t first_non_whitespace = str.find_first_not_of(" \t\n\r");
        size_t last_non_whitespace = str.find_last_not_of(" \t\n\r");
        if (first_non_whitespace == std::string_view::npos || last_non_whitespace == std::string_view::npos) {
            // String is empty or consists of only whitespace
            return std::string_view();
        }
        return str.substr(first_non_whitespace, last_non_whitespace - first_non_whitespace + 1);
    }

    std::string&& Trim_Space_Front_Back(std::string&& str) 
    {
        // Trim leading whitespace
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
            return !std::isspace(ch);
            }));

        // Trim trailing whitespace
        str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
            return !std::isspace(ch);
            }).base(), str.end());

        // Return the modified string as an rvalue reference
        return std::move(str);
    }


    double Parse_Angle(const std::string_view& str)
    {
        // Find the separators in the string
        auto degree_it = std::find(str.begin(), str.end(), '°');
        auto minute_it = std::find(str.begin(), str.end(), '\'');
        auto second_it = std::find(str.begin(), str.end(), '\"');

        // Check if the separators were not found
        if (degree_it == str.end() || minute_it == str.end() || second_it == str.end()) {
            THROW_TRACE(Angle_Baldy_Formatted, " the angle is badly formated" + std::string(str));
        }

        // Extract the component parts of the angle
        std::string_view degrees_str(str.begin(), degree_it);
        std::string_view minutes_str(&*(degree_it + 1), minute_it - degree_it - 1);
        std::string_view seconds_str(&*(minute_it + 1), second_it - minute_it - 1);
        if (str.back() != 'N' && str.back() != 'S' && str.back() != 'E' && str.back() != 'W')
            THROW_TRACE(Angle_Baldy_Formatted, " the angle is badly formated missing the NSWE" + std::string(str));

        // Convert the component parts to double values
        double degrees = std::stod(std::string(degrees_str));
        double minutes = std::stod(std::string(minutes_str));
        double seconds = std::stod(std::string(seconds_str));

        // Calculate the angle in degrees
        double angle = degrees + minutes / 60 + seconds / 3600;

        // Negate the angle if the direction is S or W
        if (str.back() == 'S' || str.back() == 'W') {
            angle = -angle;
        }

        return angle;
    }
}