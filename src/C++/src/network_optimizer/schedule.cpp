#include "includes/network_optimizer/schedule.h"
#include "includes/algorithm/algorithm_station.h"

#include "includes/utils/exception_def.h"

#include <algorithm>

Schedule::Schedule(std::vector<Station_CRef>&& station_list, TimeTable&& schedule_tab,DayTemplate&& day_template) noexcept : m_station_list(station_list),m_schedule(schedule_tab),DayTemplate(std::move(day_template))
{

}

bool Schedule::Contain(const Station& station_to_find) const noexcept
{
    return std::find_if(m_station_list.begin(), m_station_list.end(), [&](const Station& station) {return station == station_to_find; }) != m_station_list.end();
}


bool Schedule::Order(const Station& first,const Station& second) const
{
    std::vector<Station_CRef>::const_iterator first_iterator  = std::find_if(m_station_list.begin(),m_station_list.end(), [&](const Station& station) {return station == first; });
    std::vector<Station_CRef>::const_iterator second_iterator = std::find_if(m_station_list.begin(),m_station_list.end(), [&](const Station& station) {return station == second; });
    if(first_iterator == m_station_list.end() || second_iterator == m_station_list.end())
        THROW(Station_Not_In_Schedule)
    else if(first_iterator == second_iterator)
        THROW(Cannot_Order_Same_Station)
    else if(first_iterator<second_iterator)
        return true;
    else
        return false;
}


std::optional<DayTime> Schedule::Get_Closest_Time_To_Station(const Algorithm_Station& start_station,const Station& end_station) const
{
    const std::optional<size_t> start_index = this->Get_Station_Index(start_station.Get());
    const std::optional<size_t> end_index = this->Get_Station_Index(end_station);

    // if station cannot be found inside schedule we suppose that this is an error
    if (!start_index)
        THROW_TRACE(Station_Not_In_Schedule, "The station " + start_station.Get().Get_Name() + " is not in schedule")
    else if(!end_index)
        THROW_TRACE(Station_Not_In_Schedule, "The station " + end_station.Get_Name() + " is not in schedule")
    else if(*start_index > *end_index)
        return std::nullopt;

    for(size_t i = 0 ;i < m_schedule[*start_index].size();i++ )
    {
        std::optional<DayTime> start_station_time = m_schedule[*start_index][i];
        if(!start_station_time.has_value())
            continue;
        else if(*start_station_time < start_station.Get_Best_Time_Start_To_Station())
            continue;
        const std::optional<DayTime> end_station_station_time = m_schedule[*end_index][i];
        if(!end_station_station_time.has_value())
            continue;
        return end_station_station_time;         
    }
    return std::nullopt;
}

std::optional<size_t> Schedule::Get_Station_Index(const Station& station_to_find) const noexcept
{
    std::vector<Station_CRef>::const_iterator it = std::find_if(m_station_list.begin(),m_station_list.end(), [&](const Station& station) {return station == station_to_find; });
    if(it == m_station_list.end())
        return std::nullopt;
    return std::distance(m_station_list.begin(),it);
}

const std::vector<Station_CRef>& Schedule::Get_Station_List() const noexcept 
{ 
    return m_station_list;
}