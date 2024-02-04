#include "includes/network/line.h"
#include "includes/algorithm/algorithm_station.h"


#include <algorithm>
#include <ranges>

int Network::Line::s_count = 0;

Network::Line::Line(std::vector<Station_CRef>&& station_list,std::string&& name) noexcept: m_stations(std::move(station_list)),m_name(std::move(name)),m_id(++s_count)
{

}

std::optional<size_t> Network::Line::Get_Station_Index(const Network::Station& station_to_find) const noexcept
{
	std::vector<Station_CRef>::const_iterator it = std::find_if(m_stations.begin(), m_stations.end(), [&](const Station& station) {return station == station_to_find; });
	if (it == m_stations.end())
		return std::nullopt;
	return std::distance(m_stations.begin(), it);
}

const std::vector<Network::Station_CRef>& Network::Line::Get_Station_List() const noexcept
{
	return m_stations;
}

bool Network::Line::Contain(const Network::Station& station_to_find) const noexcept
{
	return std::find_if(m_stations.begin(), m_stations.end(), [&](const Station& station) {return station == station_to_find; }) != m_stations.end();
}


bool Network::Line::Order(const Network::Station& first, const Network::Station& second) const
{
	std::vector<Station_CRef>::const_iterator first_iterator = std::find_if(m_stations.begin(), m_stations.end(), [&](const Station& station) {return station == first; });
	std::vector<Station_CRef>::const_iterator second_iterator = std::find_if(m_stations.begin(), m_stations.end(), [&](const Station& station) {return station == second; });
	if (first_iterator == m_stations.end() || second_iterator == m_stations.end())
		THROW(STATION_NOT_IN_SCHEDULE)
	else if (first_iterator == second_iterator)
		THROW(CANNOT_ORDER_SAME_STATION)
	else if (first_iterator < second_iterator)
		return true;
	else
		return false;
}

