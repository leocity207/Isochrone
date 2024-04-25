#ifndef NETWORK_SCHEDULE_H
#define NETWORK_SCHEDULE_H

// STL
#include <vector>
#include <optional>
#include <functional>

// Utils
#include "includes/utils/exception_def.h"
#include "includes/utils/daytime.h"
#include "includes/utils/ctor.h"

// Network
#include "includes/network/station.h"
#include "includes/network/day_info.h"
#include "includes/network/line.h"

namespace Network
{
	using  TimeTable = std::vector<std::vector<std::optional<DayTime>>>;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Timetable class represent transport schedule and meta data about the schedule
	///        Basically We suppose a schedule is a matrix containing the time at which the transport get to the station
	///        Here we suppose that the line represent the station and the column represent the pathway of one transport
	/// @note not_default_constructible
	///       not_copy_constructible
	///       not_copy_assignable
	///       move_constructible
	///       move_asignable
	class Schedule : public DayTemplate, public Line
	{
		//#####
		// CTOR
	public:
		DELETE_COPY(Schedule)
		DELETE_DEFAULT_CTOR(Schedule)
		DEFAULT_MOVE(Schedule)

		////////////////////////////////////////////////////
		/// @brief              Explicit constructor by move construction
		/// @param station_list List of station that schedule
		/// @param schedule_tab The timetable of the schedule
		/// @param day_template The type of day the scheedule is applied
		/// @param name         The name of the schedule
		Schedule(std::vector<Station_CRef>&& station_list, TimeTable&& schedule_tab, DayTemplate&& day_template,std::string&& name) noexcept;

		//########
		// METHODS
	public:

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief               Find the closest time to go from start to finish station knowing the curent daytime and the daytype
		/// @param start_station The station you want to get on
		/// @param end_station   The station you want to get out
		/// @param current_time  The time at wich you start waiting at the start station
		/// @return              The arriving daytime at the end station. if no path were found it return an invalid daytime
		std::optional<DayTime> Get_Closest_Time_To_Station(const Station& start_station, const Station& end_station, const DayTime& startStationTime) const;


		//###########
		// ATTRIBUTES
	private:
		TimeTable m_timetable;
	};

	using Schedule_CRef = std::reference_wrapper<const Schedule>;

} // Network


#endif //NETWORK_SCHEDULE_H