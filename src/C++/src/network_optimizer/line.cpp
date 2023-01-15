#include "line.h"
#include "includes/network_optimizer/line.h"
#include "includes/algorithm/algorithm_station.h"


#include <algorithm>
#include <ranges>
#include <cassert>

int Line::s_count = 0;

Line::Line(std::vector<Schedule>&& Schedule,std::string&& name) noexcept: m_schedule(std::move(Schedule)),m_name(std::move(name)),m_id(++s_count)
{

}


std::optional<DayTime_CRef> Line::Get_Closest_Time_To_Station(const Algorithm_Station& start_station,const Station& end_station,const Day& matching_day) const noexcept
{
    std::optional<Schedule_CRef> selected_schedule = this->Get_Schedule(matching_day, start_station.Get(), end_station);
    if(!selected_schedule.has_value())
        return std::nullopt;
    return selected_schedule->get().Get_Closest_Time_To_Station(start_station,end_station); 
}

std::optional<Schedule_CRef> Line::Get_Schedule(const Day& matching_day,const Station& start_station,const Station& end_station) const noexcept
{
    auto start_station_ref = std::reference_wrapper<const Station>(start_station);
    auto end_station_ref = std::reference_wrapper<const Station>(end_station);
    auto does_day_match_schedule = [matching_day, start_station_ref, end_station_ref](const Schedule& i) { return i.Match(matching_day) && i.Order(start_station_ref, end_station_ref); };
    
    std::vector<Schedule_CRef> transformed(m_schedule.begin(), m_schedule.end());
    auto right_schedule = std::find_if(transformed.begin(), transformed.end(),does_day_match_schedule);
    if(right_schedule == transformed.end())
    {
        TRACE("The line" + m_name + "have no schedule for " + matching_day.Description());
        return std::nullopt;
    }
    return m_schedule[right_schedule- transformed.begin()];
}

const std::array<Schedule_CRef, 2> Line::Get_Schedules(const Day& matching_day) const noexcept
{
    std::vector<Schedule_CRef> temp;
    std::copy_if(m_schedule.begin(), m_schedule.end(), std::back_inserter(temp), [&](const Schedule& schedule) {return schedule.Match(matching_day);});
    assert(temp.size() == 2);
    return {std::move(temp[0]),std::move(temp[1])};
}

bool Line::Contain(const Station& station, const Day& matching_day) const noexcept
{
    std::reference_wrapper<const Station> station_ref = station;
    const std::array<Schedule_CRef, 2> temp = this->Get_Schedules(matching_day);
    return temp[0].get().Contain(station_ref) || temp[1].get().Contain(station_ref);
}