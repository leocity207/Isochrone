#include "includes/network/station.h"

int Network::Station::s_count = 0;

Network::Station::Station(Sphere_Coordinate&& coordinate, std::string&& name) noexcept : m_coordinate(coordinate), m_name(name), m_id(++s_count)
{

}

const double Network::Station::Get_Distance_To(const Station& station) const noexcept
{
	return m_coordinate.Get_Distance(station.GetCoordinate());
}

const double Network::Station::Get_Distance_To(const Sphere_Coordinate& coordinate) const noexcept
{
	return m_coordinate.Get_Distance(coordinate);
}

const std::string& Network::Station::Get_Name() const noexcept
{ 
	return m_name; 
}

const Sphere_Coordinate& Network::Station::GetCoordinate() const noexcept
{
	 return m_coordinate; 
}

bool Network::Station::operator==(const Station& other_station) const noexcept
{ 
	return m_id == other_station.m_id;
}

bool Network::Station::operator!=(const Station& other_station) const noexcept
{ 
	return m_id != other_station.m_id;
}

bool Network::Station::operator<(const Station& other_station) const noexcept
{ 
	return m_id < other_station.m_id;
}