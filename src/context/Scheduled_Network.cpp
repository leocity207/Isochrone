#include "includes/context/Scheduled_Network.h"

Context::Scheduled_Network::Scheduled_Network(std::vector<Network::Scheduled_Line>&& lines, std::vector<Network::Station>&& stations) noexcept : m_lines(std::move(lines)), m_stations(std::move(stations))
{

}

const std::vector<Network::Station>& Context::Scheduled_Network::Get_Station() const noexcept
{
	return m_stations;
}

const std::vector<Network::Scheduled_Line>& Context::Scheduled_Network::Get_Scheduled_Lines() const noexcept
{
	return m_lines;
}
