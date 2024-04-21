#ifndef CONTEXT_SCHEDULED_NETWORK_H
#define CONTEXT_SCHEDULED_NETWORK_H

// Network
#include "includes/network/scheduled_line.h"
#include "includes/network/station.h"

// utils
#include "includes/utils/ctor.h"


namespace Context
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Context used to agregate everything about a scheduled network including the scheduled lines information and the station composing it
	/// @note not_default_constructible
	///       not_copy_constructible
	///       not_copy_assignable
	///       move_constructible
	///       move_asignable
	class Scheduled_Network
	{
	//#####
	// CTOR
	public:
		DELETE_DEFAULT_CTOR(Scheduled_Network);
		DELETE_COPY(Scheduled_Network);
		DEFAULT_MOVE(Scheduled_Network);
		
		////////////////////////////////////////////////////
		/// @brief Explicit constructor by move construction
		Scheduled_Network(std::vector<Network::Scheduled_Line>&& lines, std::vector<Network::Station>&& stations) noexcept;

	//########
	// METHODS
	public:

		///////////////////////////////////////////////////////////////
		/// @brief Get the list of station inside the scheduled network
		const std::vector<Network::Station>& Get_Station() const noexcept;

		/////////////////////////////////////////////////////////////
		/// @brief Get the list of all scheduled line inside the scheduled network
		const std::vector<Network::Scheduled_Line>& Get_Scheduled_Lines() const noexcept;


	//###########
	// ATTRIBUTES
	private:
		std::vector<Network::Scheduled_Line> m_lines;
		std::vector<Network::Station> m_stations;
	};

}// Context


#endif // CONTEXT_SCHEDULED_NETWORK_H