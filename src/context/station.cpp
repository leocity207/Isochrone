#include "includes/algorithm/algorithm_station.h"
#include "includes/algorithm/network_optimizer.h"

#include <algorithm>
#include <vector>

#include "includes/utils/exception_def.h"

Context::Station::Station(const Network:: Station& station_to_link) noexcept : m_best_time(), m_basic_time(),m_reach_by_transport(false), m_ref_station(station_to_link)
{
	m_best_time = m_optimizer->Get_Start_Time() + std::chrono::seconds((long)(std::round(m_ref_station->Get_Distance_To(m_optimizer->Get_Start_Coordinate()) / m_optimizer->Get_Speed())));
	m_basic_time = m_best_time;
}
	
const Network::Station& Context::Station::Get() const noexcept
{
	return *m_ref_station;
}


DayTime Context::Station::Get_Best_Time_Start_To_Station() const noexcept
{
	return m_best_time;
}

void Context::Station::Try_Set_New_Best_Time(DayTime& new_value)
{
	if(m_best_time>new_value)
		m_best_time = new_value;
}

void Context::Station::Try_Set_New_Best_Time(std::optional<DayTime>& new_value)
{
	if(new_value.has_value() && m_best_time>*new_value)
		m_best_time = *new_value;
}

bool Context::Station::Is_Reach_Faster_Than(const Algorithm_Station& other_station) const noexcept
{ 
	return m_best_time < other_station.m_best_time;
}


const Context::Station& Context::Station::Get_Station_By_Name(const std::vector<Algorithm_Station>& station_list,const std::string& name)
{

	auto it = std::find_if(station_list.begin(), station_list.end(), [&](const Algorithm_Station& other_station) {
		return other_station.Get().Get_Name() == name;
	});

	if (it == station_list.end())
		throw TIME_BADLY_FORMATED();
	return *it;
}
