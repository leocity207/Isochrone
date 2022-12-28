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

const std::string Day::Description() const noexcept
{
    const std::string weekday[WEEKDAY_COUNT] = { "sunday", "monday", "tuesday", "wednesday","thursday","friday","saturday"};
    const std::string day_type[DAY_TYPE_COUNT] = {"school day","vacation day","holy day"};
    return weekday[m_weekday.c_encoding()] + day_type[(int)m_day_type];
}

bool Day::operator==(const Day& other) const noexcept
{
    return m_day_type == other.m_day_type && m_weekday == other.m_weekday;
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
    if(m_working_days[day.GetWeekday().c_encoding()] && m_working_types[day.GetDayType()])
        return true;
    return false;
}

bool DayTemplate::operator==(const DayTemplate& other) const noexcept
{
    if (m_working_days == other.m_working_days)
        return true;
    return false;
}