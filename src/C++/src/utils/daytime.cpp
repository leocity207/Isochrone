#include "includes/utils/daytime.h"

#include "includes/utils/exception_def.h"
#include "includes/utils/general.h"

#include <string_view>


DayTime::DayTime(std::chrono::hours hours, std::chrono::minutes minutes) noexcept : m_day_minute(hours*60+minutes)
{

}

bool DayTime::operator>(const DayTime& other_DayTime) const noexcept
{
}
bool DayTime::operator<(const DayTime& other_DayTime) const noexcept
{
}
bool DayTime::operator>=(const DayTime& other_DayTime) const noexcept
{
}
bool DayTime::operator<=(const DayTime& other_DayTime) const noexcept
{
}

static std::optional<DayTime> DayTime::From_Time_String(const std::string_view& description)
{
    // Trim leading and trailing whitespace
    time_string = std::string_view(time_string.data(), time_string.size());
    size_t first_non_whitespace = time_string.find_first_not_of(" \t\n\r");
    size_t last_non_whitespace = time_string.find_last_not_of(" \t\n\r");
    if (first_non_whitespace == std::string_view::npos || last_non_whitespace == std::string_view::npos) {
        // String is empty or consists of only whitespace
        return std::nullopt;
    }
    time_string = time_string.substr(first_non_whitespace, last_non_whitespace - first_non_whitespace + 1);

    // Find the position of the ':' character
    size_t colon_pos = time_string.find(':');
    if (colon_pos == std::string_view::npos) {
        // No colon found, throw an exception
        throw std::invalid_argument("Invalid time string: no colon found");
    }

    // Extract the hour and minute strings
    std::string_view hour_string = time_string.substr(0, colon_pos);
    std::string_view minute_string = time_string.substr(colon_pos + 1);

    // Convert the strings to integers
    int hours = std::stoi(std::string(hour_string));
    int minutes = std::stoi(std::string(minute_string));

    // Return the result as a pair
    return std::make_pair(hours, minutes);
}

