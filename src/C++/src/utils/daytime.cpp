#include "includes/utils/daytime.h"

#include "includes/utils/exception_def.h"
#include "includes/utils/general.h"

#include <string_view>
#include <chrono>


DayTime::DayTime(std::chrono::hours hours, std::chrono::minutes minutes) noexcept : m_day_minute(hours+minutes)
{

}

bool DayTime::operator>(const DayTime& other_DayTime) const noexcept
{
    return m_day_minute > other_DayTime.m_day_minute;
}
bool DayTime::operator<(const DayTime& other_DayTime) const noexcept
{
    return m_day_minute < other_DayTime.m_day_minute;
}
bool DayTime::operator>=(const DayTime& other_DayTime) const noexcept
{
    return m_day_minute >= other_DayTime.m_day_minute;
}
bool DayTime::operator<=(const DayTime& other_DayTime) const noexcept
{
    return m_day_minute <= other_DayTime.m_day_minute;
}

std::optional<DayTime> DayTime::From_Time_String(const std::string_view& time_string)
{
    std::string_view sub_str = Generals::Trim_Space_Front_Back(time_string);
    if (sub_str.size() == 0)
        return std::nullopt;

    // Find the position of the ':' character
    size_t colon_pos = sub_str.find(':');
    if (colon_pos == std::string_view::npos) {
        // No colon found, throw an exception
        THROW_TRACE(Time_Badly_Formatted,"Invalid time string: no colon found " + std::string(time_string));
    }

    // Extract the hour and minute strings
    std::string_view hour_string = sub_str.substr(0, colon_pos);
    std::string_view minute_string = sub_str.substr(colon_pos + 1);
    

    // Convert the strings to integers
    int hours;
    int minutes;
    try
    {
        hours = std::stoi(hour_string.data());
        minutes  = std::stoi(minute_string.data());
    }
    catch (std::invalid_argument&)
    {
        THROW_TRACE(Time_Badly_Formatted, "Invalid time string: no colon found " + std::string(time_string));
    }
    return DayTime(std::chrono::hours(hours), std::chrono::minutes(minutes));
    // Return the result as a pair
    
}


const std::chrono::minutes& DayTime::GetTime()
{
    return m_day_minute;
}

