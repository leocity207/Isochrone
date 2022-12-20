#include "includes/utils/general.h"

#include <algorithm>
#include <cctype>
#include <ranges>

namespace General
{
        
    std::string_view Trim_Space_Front_Back(const std::string_view& str)
    {
        // Find the first non-whitespace character
        auto first = std::find_if(str.begin(), str.end(), [](char c) {
            return !std::isspace(c);
            });

        // Find the last non-whitespace character
        auto last = std::find_if(str.rbegin(), str.rend(), [](char c) {
            return !std::isspace(c);
            }).base();

            // Return a new string_view that includes only the non-whitespace characters

            return std::string_view(&*first, last - first);
            // to do used ranges::subview
    }
}