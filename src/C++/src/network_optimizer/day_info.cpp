#include "includes/network_optimizer/day_info.h"

#include <algorithm>

Day::Day(const std::chrono::weekday weekday,const DAY_TYPE day_type) noexcept : m_weekday(weekday), m_day_type(day_type)
{

}

const std::chrono::weekday& Day::GetWeekday() const noexcept
{
    return m_weekday;
}

const DAY_TYPE& Day::GetDayType() const noexcept
{
    return m_day_type;
}

//------------------------------------------
//
//
//
//
//------------------------------------------

DayTemplate::DayTemplate(const std::array<bool,WEEKDAY_COUNT> working_day,const std::array<bool,DAY_TYPE_COUNT> working_types) noexcept : m_working_days(working_day),m_working_types(working_types)
{

}

DayTemplate::DayTemplate(DayTemplate&& template_to_move) noexcept : m_working_days(std::move(template_to_move.m_working_days)),m_working_types(std::move(template_to_move.m_working_types))
{

}

bool DayTemplate::Match(const Day& day) const noexcept
{
    if(std::find(m_working_days.cbegin(),m_working_days.cend(),day.GetWeekday() != m_working_days.cend())  &&  std::find(m_working_types.cbegin(),m_working_types.cend(),day.GetDayType()) != m_working_types.cend())
        return true;
    return false;
}