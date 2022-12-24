#include "includes/algorithm/algorithm_station.h"


Algorithm_Station::Algorithm_Station(Sphere_Coordinate&& coordinate, std::string&& name) noexcept : Station(std::move(coordinate),std::move(name)), m_best_time(std::chrono::hours(0),std::chrono::minutes(0)), m_reach_by_transport(false)
{

}


std::optional<DayTime> Algorithm_Station::Get_Best_Time_Start_To_Station() const noexcept
{
	return std::nullopt;
}