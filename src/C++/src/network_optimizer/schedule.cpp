#include "includes/network_optimizer/schedule.h"
#include "includes/algorithm/algorithm_station.h"

#include <algorithm>

Schedule::Schedule(std::vector<Station&>&& station_list, TimeTable&& schedule_tab,DayTemplate&& day_template) noexcept : m_station_list(station_list),m_schedule(schedule_tab),DayTemplate(std::move(day_template))
{

}


bool Schedule::Contain(const Station& station_to_find)
{
    return std::find(m_station_list.begin(),m_station_list.end(),station_to_find) != m_station_list.end();
}

bool Schedule::Order(const Station& first,const Station& second) noexcept const
{
    std::vector<Station_CRef>::iterator first_iterator = std::find(m_station_list.begin(),m_station_list.end(),first);
    std::vector<Station_CRef>::iterator second_iterator = std::find(m_station_list.begin(),m_station_list.end(),second);
    if(first_iterator<second_iterator)
        return true;
    return false;
}


std::optional<DayTime_CRef> Schedule::Get_Closest_Time_To_Station(const Algorithm_Station& start_station,const Station& end_station,const DayTime& current_time) const
{
    const std::optional<size_t> start_index = this->Get_Station_Index(start_station);
    const std::optional<size_t> end_index = this->Get_Station_Index(end_station);

    // if station cannot be found inside schedule we suppose that this is an error
    if(!start_index)
        THROW_TRACE(Station_Not_In_Schedule,"The station " + start_station.Get_Name() " is not in schedule");
    else if(!end_index)
        THROW_TRACE(Station_Not_In_Schedule,"The station " + end_station.Get_Name() " is not in schedule");

    for(const std::vector<std::optional<DayTime>>& schedule_line : m_schedule)
    {
        const std::optional<DayTime> start_station_time = schedule_line[schedule_line.begin()+*start_index]
        if(!start_station_time.has_value())
            continue;
        else if(start_station_time->get() > start_station.Get_Best_Time_Start_To_Station().)
            continue;
        const std::optional<DayTime> end_station_station_time = schedule_line[schedule_line.begin()+*end_index]
        if(!end_station_station_time.has_value())
            continue;
        return end_station_station_time->get();         
    }
    return std::nullopt;
}

std::optional<size_t> Schedule::Get_Station_Index(const Station& station_to_find)
{
    std::vector<Station_CRef>::iterator it = std::find(m_station_list.begin(),m_station_list.end(),station_to_find);
    if(it == m_station_list.end())
        return std::nullopt;
    return std::distance(m_station_list.begin(),it);
}