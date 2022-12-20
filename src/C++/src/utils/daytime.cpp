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
    

    const auto middle = std::find(description.begin(), description.end(), ':');
    if (middle == description.end())
        return std::nullopt;
    
    const std::string_view hour_str = General::Trim_Space_Front_Back()


    std::string_view left;
    chunk.assign(std::make_move_iterator(start), std::make_move_iterator(end));
    chunks.emplace_back(std::move(chunk));
    start = end;
    if (start != line.end()) {
        ++start;
    }

}

