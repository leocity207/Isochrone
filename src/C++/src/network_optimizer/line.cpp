#include "includes/network_optimizer/line.h"

#include <algorithm>

Line::Line(std::vector<Schedule>&& Schedule,std::string&& name) noexcept: m_schedule(Schedule),m_name(name),m_id(++s_count)
{

}


std::optional<DayTime_CRef> Line::Get_Closest_Time_To_Station(const Station& start_station,const Station& end_station,const DayTime& current_time,const Day& matching_day) const
{
    std::optional<Schedule_CRef> selected_schedule = this->Get_Schedule(matching_day,start_station,end_station)
    if(!selected_schedule)
        return std::nullopt;
    return selected_schedule->Get_Closest_Time_To_Station(start_station,end_station,current_time); 
}

const Schedule& Line::Get_Schedule(const Day& matching_day,const Station& start_station,const Station& end_station)
{
    auto does_day_match_schedule = [day_template](Schedule i){ return i.Match(day_template) && i.Order(start_station,end_station)};
    auto right_schedule = std::find_if(m_schedule.begin(),m_schedule.end(),does_day_match_schedule);
    if(right_schedule == m_schedule.end())
    {
        TRACE(No_Matching_Schedule,"The line" + m_name + "have no schedule for " + matching_day.Description());
        return S_INVALID_SCHEDULE;
    }
    return m_schedule[right_schedule-m_schedule.begin()];
}