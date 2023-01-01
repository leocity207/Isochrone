#include "includes/algorithm/algorithm_station.h"
#include "includes/algorithm/network_optimizer.h"

Algorithm_Station::Algorithm_Station(const Station* station_to_link, const Network_Optimizer* optimizer) noexcept : m_best_time(), m_reach_by_transport(false), m_ref_station(station_to_link), m_optimizer(optimizer)
{
	m_best_time = this->Get_Best_Time_Start_To_Station();
}
	
const Station& Algorithm_Station::Get() const noexcept
{
	return *m_ref_station;
}

const Station& Algorithm_Station::operator*() const noexcept
{
	return *m_ref_station;
}

DayTime Algorithm_Station::Get_Best_Time_Start_To_Station() const noexcept
{
	static DayTime time = m_optimizer->Get_Start_Time() + std::chrono::seconds((long)(m_optimizer->Get_Speed() * m_ref_station->Get_Distance_To(m_optimizer->Get_Start_Coordinate())));
	return time;
}

void Algorithm_Station::Try_Set_New_Best_Time(DayTime& new_value)
{
	if(m_best_time>new_value)
		m_best_time = new_value;
}

void Algorithm_Station::Try_Set_New_Best_Time(std::optional<DayTime>& new_value)
{
	if(new_value.has_value() && m_best_time>*new_value)
		m_best_time = *new_value;
}

