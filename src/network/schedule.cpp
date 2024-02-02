#include "includes/network/schedule.h"
#include "includes/algorithm/algorithm_station.h"

#include "includes/utils/exception_def.h"

#include <algorithm>

Network::Schedule::Schedule(std::vector<Network::Station_CRef>&& station_list, Network::TimeTable&& schedule_tab, Network::DayTemplate&& day_template) noexcept : m_station_list(station_list), m_timetable(schedule_tab),DayTemplate(std::move(day_template))
{

}

bool Network::Schedule::Contain(const Network::Station& station_to_find) const noexcept
{
	return std::find_if(m_station_list.begin(), m_station_list.end(), [&](const Station& station) {return station == station_to_find; }) != m_station_list.end();
}


bool Network::Schedule::Order(const Network::Station& first,const Network::Station& second) const
{
	std::vector<Station_CRef>::const_iterator first_iterator  = std::find_if(m_station_list.begin(),m_station_list.end(), [&](const Station& station) {return station == first; });
	std::vector<Station_CRef>::const_iterator second_iterator = std::find_if(m_station_list.begin(),m_station_list.end(), [&](const Station& station) {return station == second; });
	if(first_iterator == m_station_list.end() || second_iterator == m_station_list.end())
		THROW(STATION_NOT_IN_SCHEDULE)
	else if(first_iterator == second_iterator)
		THROW(CANNOT_ORDER_SAME_STATION)
	else if(first_iterator<second_iterator)
		return true;
	else
		return false;
}


std::optional<DayTime> Network::Schedule::Get_Closest_Time_To_Station(const Station& start_station,const Station& end_station,const DayTime& startStationTime) const
{
	const std::optional<size_t> start_index = this->Get_Station_Index(start_station);
	const std::optional<size_t> end_index = this->Get_Station_Index(end_station);

	// if station cannot be found inside schedule we suppose that this is an error
	if (!start_index)
		THROW_TRACE(STATION_NOT_IN_SCHEDULE, "The station " + start_station.Get_Name() + " is not in schedule")
	else if (!end_index)
		THROW_TRACE(STATION_NOT_IN_SCHEDULE, "The station " + end_station.Get_Name() + " is not in schedule")
	else if(*start_index > *end_index)
		return std::nullopt;

	for(size_t i = 0 ;i < m_timetable[*start_index].size();i++ )
	{
		std::optional<DayTime> start_station_time = m_timetable[*start_index][i];
		if(!start_station_time.has_value())
			continue;
		else if(*start_station_time < startStationTime)
			continue;
		const std::optional<DayTime> end_station_station_time = m_timetable[*end_index][i];
		if(!end_station_station_time.has_value())
			continue;
		return end_station_station_time;         
	}
	return std::nullopt;
}

std::optional<size_t> Network::Schedule::Get_Station_Index(const Network::Station& station_to_find) const noexcept
{
	std::vector<Station_CRef>::const_iterator it = std::find_if(m_station_list.begin(),m_station_list.end(), [&](const Station& station) {return station == station_to_find; });
	if(it == m_station_list.end())
		return std::nullopt;
	return std::distance(m_station_list.begin(),it);
}

const std::vector<Network::Station_CRef>& Network::Schedule::Get_Station_List() const noexcept
{ 
	return m_station_list;
}