#ifndef CONTEXT_SCHEDULED_NETWORK_H
#define CONTEXT_SCHEDULED_NETWORK_H

// Network
#include "includes/network/scheduled_line.h"
#include "includes/network/station.h"

// utils
#include "includes/utils/ctor.h"


namespace Context
{
	class Scheduled_Network
	{
	//#####
	// CTOR
	public:
		DELETE_DEFAULT_CTOR(Scheduled_Network);
		DELETE_COPY(Scheduled_Network);
		DEFAULT_MOVE(Scheduled_Network);
		
		Scheduled_Network(std::vector<Network::Scheduled_Line>&& lines, std::vector<Network::Station>&& stations) noexcept;

	//########
	// METHODS
	public:
		const std::vector<Network::Station>& Get_Station() const noexcept;
		const std::vector<Network::Scheduled_Line>& Get_Scheduled_Lines() const noexcept;


	//###########
	// ATTRIBUTES
	private:
		std::vector<Network::Scheduled_Line> m_lines;
		std::vector<Network::Station> m_stations;
	};

}// Context


#endif // CONTEXT_SCHEDULED_NETWORK_H