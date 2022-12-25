#include "includes/algorithm/algorithm_station.h"


Algorithm_Station::Algorithm_Station(const Station& station_to_link) noexcept : m_best_time(std::chrono::hours(0), std::chrono::minutes(0)), m_reach_by_transport(false), m_ref_station(station_to_link)
{

}

const Station& Algorithm_Station::Get() const noexcept
{
	return m_ref_station;
}

const Station& Algorithm_Station::operator*() const noexcept
{
	return m_ref_station;
}

std::optional<DayTime> Algorithm_Station::Get_Best_Time_Start_To_Station() const noexcept
{
	return std::nullopt;
}