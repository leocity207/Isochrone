#include "includes/network_optimizer/station.h"

int Station::s_count = 0;

Station::Station(Sphere_Coordinate&& coordinate, std::string&& name) noexcept : m_coordinate(coordinate), m_name(name), m_id(++s_count)
{

}

Station::Station(Station&& other_station) noexcept : m_coordinate(std::move(other_station.m_coordinate)), m_name(std::move(other_station.m_name)), m_id(other_station.m_id)
{

}

const Sphere_Coordinate& Station::GetCoordinate() const noexcept 
{
    return m_coordinate;
}

const double Station::Get_Distance_To(const Station& station) const noexcept
{
    return m_coordinate.Get_Distance(station.GetCoordinate());
}

const double Station::Get_Distance_To(const Sphere_Coordinate& coordinate) const noexcept
{
    return m_coordinate.Get_Distance(coordinate);
}

bool Station::operator==(const Station& other_station) const noexcept
{
    return m_id == other_station.m_id;
}

const std::string& Station::Get_Name() const noexcept  
{
    return m_name;
}