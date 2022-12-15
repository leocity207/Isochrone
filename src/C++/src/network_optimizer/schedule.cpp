#include "includes/network_optimizer/schedule.h"

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
    std::vector<Station&>::iterator first_iterator = std::find(m_station_list.begin(),m_station_list.end(),first);
    std::vector<Station&>::iterator second_iterator = std::find(m_station_list.begin(),m_station_list.end(),second);
    if(first_iterator<second_iterator)
        return true;
    return false;
}


std::optional<DayTime_CRef> Schedule::Get_Closest_Time_To_Station(const Station& start_station,const Station& end_station,const DayTime& current_time)
{
    const std::optional< std::vector< std::optional< DayTime>>::iterator> start_index = this->Get_Station_Index(start_station);
    const std::optional< std::vector< std::optional< DayTime>>::iterator> end_index = this->Get_Station_Index(end_station);

    // if station cannot be found inside schedule we suppose that this is an error
    if(!start_index)
        THROW_TRACE(Station_Not_In_Schedule,"The station " + start_station.Get_Name() " is not in schedule");
    else if(!end_index)
        THROW_TRACE(Station_Not_In_Schedule,"The station " + end_station.Get_Name() " is not in schedule");

    for(const std::vector<std::optional<DayTime>>& schedule_line : m_schedule)
    {
        const std::optional<DayTime> start_station_time = schedule_line[schedule_line.begin()-start_index.get()]
        if(!start_station_time.has_value())
            continue;
        else if(start_station_time->get() > start_station.Get_Best_Travel_Time_Start_To_Station())
            continue;
        const std::optional<DayTime> end_station_station_time = schedule_line[schedule_line.begin()-end_index.Get()]
        if(!end_station_station_time.has_value())
            continue;
        return end_station_station_time->get();         
    }
    return std::nullopt;
}

     i = 0
    # find the first passing time that is valid
    while(i<len(timetable[0])-1 and (timetable[index_start][i] is None or timetable[index_start][i] <start_station.Get_Best_Travel_Time_Start_To_Station()) ):
        i+=1
    #if nothing was found just return nothing 
    if(i == len(timetable[0])-1 ):
        return -1

    #try to find a path from start to end that could match 
    while(i<len(timetable[0])-1):
        if(not(timetable[index_end][i] is None) and not(timetable[index_start][i] is None)):
            return timetable[index_end][i] #yes we found a matching path
        i+=1
    
    #if we just don't fidna  path from start to end that mean none exist
    return -1
}

std::optional<size_t> Schedule::Get_Station_Index(const Station& station_to_find)
{
    std::vector<Station&>::iterator it = std::find(m_station_list.begin(),m_station_list.end(),station_to_find);
    if(it == m_station_list.end())
        return std::nullopt;
    return std::distance(m_station_list.begin());
}

std::optional<std::vector<std::optional<DayTime>>::iterator> Schedule::Get_Station_Index(const Station& station_to_find)
{
    std::vector<Station&>::iterator it = std::find(m_station_list.begin(),m_station_list.end(),station_to_find);
    if(it == m_station_list.end())
        return std::nullopt;
    return it;
}