#ifndef NETWORK_LINE_H
#define NETWORK_LINE_H

// STL
#include <vector>
#include <ranges>

// Logs
#include "submodule/Logger/includes/exception.h"

// Utils
#include "includes/utils/exception_def.h"
#include "includes/utils/ctor.h"

// Network
#include "includes/network/station.h"


namespace Network
{
	class Line
	{
	////////
	/// CTOR
	public:
		DELETE_COPY(Line)
		DELETE_DEFAULT(Line)
		DEFAULT_MOVE(Line)

		Line(std::vector<Station_CRef>&& Schedule,std::string&& name) noexcept;

	///////////
	/// METHODS
	public:
		//////////////////////////////////////////////////////////////////
		/// @brief give back the station list of the schedule
		/// @return a list of reference to the station inside the schedule
		const std::vector<Station_CRef>& Get_Station_List() const noexcept;

		/////////////////////////////////////////////////////////////////////////////
		/// @brief         : Check if the first station come before the second station
		/// @param first   : Is the supposed first station
		/// @param second  : Is the supposed later station
		/// @note          : If first or second is not part of the schedule this function throw
		/// @return        : True if second come after false
		/// @throw         : If the second or first station is not part of the schedule
		std::strong_ordering Order(const Station& first, const Station& second) const;


		/////////////////////////////////////////////////////
		/// @brief                 : check if a station is contained inside the schedule
		/// @param station_to_find : The station you want to check if present inside the schedule
		/// @return                : True if the station contain the schedule false if not
		bool Contain(const Station& station_to_find) const noexcept;

		////////////////////////////////////////////////////////////
		/// @brief                 : give the index of the station inside the schedule
		/// @param station_to_find : The station you want to find the index of
		/// @return                : An optional containing the index or not if the station could not be found 
		std::optional<size_t> Get_Station_Index(const Station& station_to_find) const noexcept;

		////////////////////////////////////////////////////////////
		/// @brief   : Give the iterator pointing to the station given in parameter inside the line
		/// @param   : Station you want to find the iterator of
		/// @return  : An optional containing the index or not if the station could not be found 
		std::vector<Station_CRef>::const_iterator From_Station(const Station& station) const noexcept;

		//////////////
		/// ATTRIBUTESs
		protected:
			std::string m_name;
			std::vector<Station_CRef> m_stations;
			int m_id;
			static int s_count;
	};

	using Line_CRef = std::reference_wrapper<Line>;

};// Network


#endif //NETWORK_LINE_H