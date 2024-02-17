#include "includes/context/reach_algorithm.h"

/// Reach algorithm
#include "includes/reach_algorithm/algorithm.h"


Context::Reach_Algorithm::Reach_Algorithm(const Scheduled_Network& network, DayTime&& start_time, double speed, Sphere_Coordinate&& starting_coordinate, Network::Day&& day_type) noexcept :
	m_network(network),
	m_start_time(std::move(start_time)),
	m_speed(speed),
	m_start_coordinate(std::move(starting_coordinate)),
	m_day_type(std::move(day_type))
{
}

const Context::Scheduled_Network& Context::Reach_Algorithm::Get_Network() const noexcept
{
	return m_network.get();
}

const DayTime& Context::Reach_Algorithm::Get_Starting_Time() const noexcept
{
	return m_start_time;
}

const double Context::Reach_Algorithm::Get_Speed() const noexcept
{
	return m_speed;
}

const Sphere_Coordinate Context::Reach_Algorithm::Get_Starting_Coordinate() const noexcept
{
	return m_start_coordinate;
}

const Network::Day& Context::Reach_Algorithm::Get_Day_Type() const noexcept
{
	return m_day_type;
}

std::vector<Context::Station> Context::Reach_Algorithm::Optimize(::Reach_Algorithm::Algorithm& algorithm) const
{
	return algorithm.Optimize(*this);
}
