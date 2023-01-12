#include "includes/algorithm/algorithm_station.h"
#include "includes/algorithm/network_optimizer.h"

#include < algorithm >
#include <vector>

DayTime initial_best_time(const Station& station_to_link,const Network_Optimizer& optimizer)
{
	return  optimizer.Get_Start_Time() + std::chrono::seconds((long)(std::round(station_to_link.Get_Distance_To(optimizer.Get_Start_Coordinate()) / optimizer.Get_Speed())));
}

Algorithm_Station::Algorithm_Station(const Station& station_to_link, const Network_Optimizer& optimizer) noexcept : m_best_time(initial_best_time(station_to_link, optimizer)),m_reach_by_transport(false) , m_linked_station(station_to_link)
{

}
	
const Station& Algorithm_Station::Get() const noexcept
{
	return m_linked_station.get();
}

DayTime Algorithm_Station::Get_Reach_Time() const noexcept
{
	return m_best_time;
}

bool Algorithm_Station::Try_Set_New_Best_Time_Transport(DayTime& new_value)
{
	if(m_best_time>new_value)
	{
		m_best_time = new_value;
		return m_reach_by_transport = m_reach_by_transport_once = true;
	}
	return false;
}

bool Algorithm_Station::Try_Set_New_Best_Time_Transport(std::optional<DayTime>& new_value)
{
	if(new_value.has_value() && m_best_time>*new_value)
	{
		m_best_time = *new_value;
		return m_reach_by_transport = m_reach_by_transport_once = true;
	}
	return false;
}

bool Algorithm_Station::Try_Set_New_Best_Time_Base(DayTime& new_value)
{
	if(m_best_time>new_value)
	{
		m_best_time = new_value;
		m_reach_by_transport = false;
		return true;
	}
	return false;
}

bool Algorithm_Station::Try_Set_New_Best_Time_Base(std::optional<DayTime>& new_value)
{
	if(new_value.has_value() && m_best_time>*new_value)
	{
		m_best_time = *new_value;
		m_reach_by_transport = false;
		return true;
	}
	return false;
}

bool Algorithm_Station::operator<(const Algorithm_Station& other_station) const noexcept 
{ 
	return m_linked_station.get() < other_station.m_linked_station.get();
}


/*static*/ const Algorithm_Station& Algorithm_Station::Get_Station_By_Name(const std::vector<Algorithm_Station>& station_list, const std::string& name)
{

	auto it = std::find_if(station_list.begin(), station_list.end(), [&](const Algorithm_Station& other_station) {
		return other_station.Get().Get_Name() == name;
	});

	if (it == station_list.end())
		throw Time_Badly_Formatted();
	return *it;
}

std::list<Algorithm_Station>::iterator& Algorithm_Station::Get_Pos() const noexcept
{
	return m_pos;
}
