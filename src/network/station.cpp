#include "includes/network/station.h"

// Utils
#include "includes/utils/exception_def.h"

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

bool Network::Station::operator<(const Station& other_station) const noexcept
{ 
	return m_id < other_station.m_id;
}

const Network::Station& Network::Station::Get_Station_By_Name(const std::vector<Network::Station>& station_list, const std::string& name)
{

	auto it = std::find_if(station_list.begin(), station_list.end(), [&](const Network::Station& other_station) {
		return other_station.Get_Name() == name;
	});

	if (it == station_list.end())
		THROW_TRACE(STATION_NOT_IN_LIST, "[error] Context::Station::Get_Station_By_Name the station cannot be found inside the list in parameter");
	return *it;
}
