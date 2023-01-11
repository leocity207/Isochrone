#include "includes/context/station.h"

//utils
#include "includes/utils/exception_def.h"

//context
#include "includes/context/reach_algorithm.h"

Context::Station::Station(const Network::Station& station_to_link, const Reach_Algorithm& reach_algorithm_context) noexcept :
	m_best_time(reach_algorithm_context.Get_Starting_Time() + std::chrono::seconds((long)(std::round(station_to_link.Get_Distance_To(reach_algorithm_context.Get_Starting_Coordinate()) / reach_algorithm_context.Get_Speed())))),
	m_basic_time(m_best_time),
	m_reach_by_transport(false),
	m_ref_station(station_to_link)
{
}
	
const Network::Station& Context::Station::Get() const noexcept
{
	return m_ref_station.get();
}


const DayTime& Context::Station::Get_Reaching_Time() const noexcept
{
	return m_best_time;
}

bool Context::Station::Try_Set_New_Best_Time_Transport(DayTime& new_value)
{
	if(m_best_time>new_value)
	{
		m_best_time = new_value;
		return m_reach_by_transport = m_reach_by_transport_once = true;
	}
	return false;
}

bool Context::Station::Try_Set_New_Best_Time_Transport(std::optional<DayTime>& new_value)
{
	if(new_value.has_value() && m_best_time>*new_value)
	{
		m_best_time = *new_value;
		return m_reach_by_transport = m_reach_by_transport_once = true;
	}
	return false;
}

bool Context::Station::Try_Set_New_Best_Time_Base(DayTime& new_value)
{
	if(m_best_time>new_value)
	{
		m_best_time = new_value;
		m_reach_by_transport = false;
		return true;
	}
	return false;
}

bool Context::Station::Try_Set_New_Best_Time_Base(std::optional<DayTime>& new_value)
{
	if(new_value.has_value() && m_best_time>*new_value)
	{
		m_best_time = *new_value;
		m_reach_by_transport = false;
		return true;
	}
	return false;
}


bool Context::Station::operator<(const  Context::Station& other_station) const noexcept
{ 
	return m_ref_station.get() < other_station.m_ref_station.get();
}

const Context::Station& Context::Station::Get_Station_By_Name(const std::vector<Context::Station>& station_list,const std::string& name)
{

	auto it = std::find_if(station_list.begin(), station_list.end(), [&](const Context::Station& other_station) {
		return other_station.Get().Get_Name() == name;
	});

	if (it == station_list.end())
		THROW(STATION_NOT_IN_LIST);
	return *it;
}

bool Context::Station::Has_Been_Reached_By_Transport() const noexcept
{
    return m_reach_by_transport;
}

bool Context::Station::Has_Been_Reached_Once_By_Transport() const noexcept
{
    return m_reach_by_transport_once;
}

void Context::Station::Set_Pos(std::list<Station>::iterator &pos)
{
	m_pos = pos;
}

const std::list<Context::Station>::iterator &Context::Station::Get_Pos() const
{
	return m_pos.value();
}
