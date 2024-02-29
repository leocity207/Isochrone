#ifndef SCHEDULED_LINE_H
#define SCHEDULED_LINE_H

// STL
#include <vector>
#include <ranges>

// Network
#include "includes/network/schedule.h"
#include "includes/network/line.h"

// Utils
#include "includes/utils/ctor.h"


namespace Network
{
	class Scheduled_Line : public Line
	{
		////////
		/// CTOR
	public:
		DELETE_COPY(Scheduled_Line)
		DELETE_DEFAULT_CTOR(Scheduled_Line)
		DEFAULT_MOVE(Scheduled_Line)

		Scheduled_Line(std::vector<Schedule>&& Schedule, std::string&& name) noexcept;

		///////////
		/// METHODS
	public:
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Find the closest time to go from start to finish station knowing the curent daytime and the daytype
		/// @param start_station the station you want to get on 
		/// @param end_station the station you want to get out
		/// @param day_template a representation of the current day
		/// @return the arriving daytime at the end station. if no path were found it return an invalid daytime
		std::optional<DayTime_CRef> Get_Closest_Time_To_Station(const Station& start_station, const Station& end_station, const DayTime& start_station_time, const Day& day) const noexcept;

		/////////////////////////////////////////////////////////////////////////
		/// @brief Get the right schedule in the line following a paterne
		/// @param matching_day the day that should match with the schedule
		/// @param start_station the station that should be before the end station
		/// @param end_station the station that should be after the start station
		/// @note the start and end station are use to determinate the direction to use
		/// @return the right schedule if found, otherwise return a void schedule
		std::optional<Schedule_CRef> Get_Schedule(const Day& matching_day, const Station& start_station, const Station& end_station) const noexcept;

		/////////////////////////////////////////////////////////////////////////////////
		/// @brief give back a list of schedules matching the day
		/// @param matching_day the day to select schedule from
		/// @return a view inside the schedule list containing only the good schedule
		auto Get_Schedules(const Day& matching_day) const noexcept
		{
			return std::views::filter(m_schedule, [matching_day](const Schedule& schedule) { return schedule.Match(matching_day); });
		};

		/////////////////////////////////////////////////////////////////////////////////
		/// @brief return true if the station is contained inside the schedules for the matching day
		/// @param matching_day the day to select schedule from
		/// @param station the station we are trying to see if contained inside the schedule
		/// @return wether or not the station is contained inside the line for this day
		bool Contain(const Station& station, const Day& matching_day) const noexcept;

	//////////////////
	/// STATIC METHDOS
	private: 
		std::vector<Station_CRef> Construct_Station_From_Schedules(const std::vector<Schedule>&);

		//////////////
		/// ATTRIBUTESs
	private:
		std::vector<Schedule> m_schedule;
	};

	using Scheduled_Line_CRef = std::reference_wrapper<Scheduled_Line>;

};// Network


#endif //SCHEDULED_LINE_H