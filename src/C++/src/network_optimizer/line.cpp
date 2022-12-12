#include "includes/network_optimizer/line.h"

#include <algorithm>

Line::Line(std::vector<Schedule>&& Schedule,std::string&& name) noexcept: m_schedule(Schedule),m_name(name),m_id(++s_count)
{

}


DayTime& Line::Get_Best_Time_To_Station(const Station& start_station,const Station& end_station,const DayTime& current_time,const Day& day_template) const
{
    const Schedule& selected_schedule = 
    if(!this->Contain(start_station))
        THROW_TRACE(Station_Not_In_Line,"The station " + start_station.Get_Name() " is not in " + m_name);
    else if(!this->Contain(end_station))
        THROW_TRACE(Station_Not_In_Line,"The station " + end_station.Get_Name() " is not in " + m_name);
    
    
}


bool Line::Contain(const Station& station_to_find,const Day& day_template)
{
    auto does_day_match_schedule = [day_template](Schedule i){ return i.Match(day_template); };
    auto right_schedule = std::find_if(m_schedule.begin(),m_schedule.end(),does_day_match_schedule);
    return m_schedule[right_schedule-m_schedule.begin()].Contain(station_to_find);   
}

const Schedule& Line::Get_Schedule(const Day& matching_day)
{
    auto does_day_match_schedule = [day_template](Schedule i){ return i.Match(day_template); };
    auto right_schedule = std::find_if(m_schedule.begin(),m_schedule.end(),does_day_match_schedule);
    if(right_schedule == m_schedule.end())
        THROW_TRACE(No_Matching_Schedule,"The line" + m_name + "have no schedule for " + matching_day.Description());
    return m_schedule[right_schedule-m_schedule.begin()];
}