#include "includes/utils/daytime.h"


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