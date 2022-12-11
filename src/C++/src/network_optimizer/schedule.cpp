#include "includes/network_optimizer/schedule.h"

#include <algorithm>
Schedule::Schedule(std::vector<Station&>&& station_list, TimeTable&& schedule_tab,DayTemplate&& day_template) noexcept : m_station_list(station_list),m_schedule(schedule_tab),DayTemplate(std::move(day_template))
{

}


bool Schedule::Contain(const Station& station_to_find)
{
    return std::find(m_station_list.begin(),m_station_list.end(),station_to_find) != m_station_list.end();

}