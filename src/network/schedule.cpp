#include "includes/network/schedule.h"

#include "includes/utils/exception_def.h"

#include <algorithm>

Network::Schedule::Schedule(std::vector<Network::Station_CRef>&& station_list, Network::TimeTable&& schedule_tab, Network::DayTemplate&& day_template,std::string&& name) noexcept : m_timetable(schedule_tab),DayTemplate(std::move(day_template)),Line(std::move(station_list),std::move(name))
{

}


std::optional<DayTime> Network::Schedule::Get_Closest_Time_To_Station(const Station& start_station,const Station& end_station,const DayTime& startStationTime) const
{
	const std::optional<size_t> start_index = this->Get_Station_Index(start_station);
	if(!start_index)
		return std::nullopt;
	const std::optional<size_t> end_index = this->Get_Station_Index(end_station);

	// if station cannot be found inside schedule we suppose that this is an error
	if (!end_index || *start_index > *end_index)
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

