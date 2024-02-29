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


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Timetable class represent transport schedule and meta data about the schedule
// Basically We suppose a schedule is a matrix containing the time at which the transport get to the station
// Here we suppose that the line represent the station and the column represent the pathway of one transport
// Needed meta data are as follow:
namespace Network
{
    using  TimeTable = std::vector<std::vector<std::optional<DayTime>>>;
    class Schedule : public DayTemplate, public Line
    {
        ////////
        /// CTOR
    public:
        //deleted
        DELETE_COPY(Schedule)
        DELETE_DEFAULT_CTOR(Schedule)
        DEFAULT_MOVE(Schedule)

        Schedule(std::vector<Station_CRef>&& station_list, TimeTable&& schedule_tab, DayTemplate&& day_template,std::string&&) noexcept;

        ///////////
        /// METHODS
    public:

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Find the closest time to go from start to finish station knowing the curent daytime and the daytype
        /// @param start_station the station you want to get on 
        /// @param end_station the station you want to get out
        /// @param current_time the time at wich you start waiting at the start station
        /// @return the arriving daytime at the end station. if no path were found it return an invalid daytime
        /// @throw if the second or first station is not part of the schedule
        std::optional<DayTime> Get_Closest_Time_To_Station(const Station& start_station, const Station& end_station, const DayTime& startStationTime) const;


        //////////////
        /// ATTRIBUTES
    private:
        TimeTable m_timetable;
    };

    using Schedule_CRef = std::reference_wrapper<const Schedule>;

} // Network


#endif //NETWORK_SCHEDULE_H