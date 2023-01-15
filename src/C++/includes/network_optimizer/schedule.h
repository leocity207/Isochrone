#ifndef SCHEDULE_H
#define SCHEDULE_H


#include <vector>
#include <optional>
#include <functional>

//log
#include "includes/utils/exception_def.h"

//utils
#include "includes/utils/daytime.h"

//network_optimization
#include "includes/network_optimizer/station.h"
#include "includes/network_optimizer/day_info.h"

class Algorithm_Station;


//------------------------------------------------------------------------------------------------------------
// Schedule class represent transport schedule and meta data about the schedule
// Basically We suppose a schedule is a matrix containing the time at which the transport get to the station
// Here we suppose that the line represent the station and the column represent the pathway of one transport
// Needed meta data are as follow:

typedef std::vector<std::vector<std::optional<DayTime>>> TimeTable;
class Schedule : public DayTemplate
{
    public:
        //deleted
        Schedule() = delete;
        Schedule(const Schedule& ) = delete;
        Schedule& operator=(const Schedule&) = delete;
        Schedule(Schedule&& ) noexcept = default;

        Schedule(std::vector<Station_CRef>&& station_list, TimeTable&& schedule_tab,DayTemplate&& day_template) noexcept;
        
        /////////////////////////////////////////////////////
        /// @brief check if a station is contained inside the schedule
        /// @param station_to_find the station you want to check if present inside the schedule
        /// @return true if the station contain the schedule false if not
        bool Contain(const Station& station_to_find) const noexcept;

        ////////////////////////////////////////////////////////////
        /// @brief give the index of the station inside the schedule
        /// @param station_to_find the station you want to find the index of
        /// @return an optional containing the index or not if the station could not be found 
        std::optional<size_t> Get_Station_Index(const Station& station_to_find) const noexcept;

        /// @brief check if the first station come before the second station
        /// @param first  is the supposed first station
        /// @param second  is the supposed later station
        /// @note if first or second is not part of the schedule this function throw
        /// @return true if second come after false
        /// @throw if the second or first station is not part of the schedule
        std::strong_ordering Order(const Station& first,const Station& second) const;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Find the closest time to go from start to finish station knowing the curent daytime and the daytype
        /// @param start_station the station you want to get on 
        /// @param end_station the station you want to get out
        /// @param current_time the time at wich you start waiting at the start station
        /// @return the arriving daytime at the end station. if no path were found it return an invalid daytime
        /// @throw if the second or first station is not part of the schedule
        std::optional<DayTime> Get_Closest_Time_To_Station(const Algorithm_Station& start_station,const Station& end_station) const;

        //////////////////////////////////////////////////////////////////
        /// @brief give back the station list of the schedule
        /// @return a list of reference to the station inside the schedule
        const std::vector<Station_CRef>& Get_Station_List() const noexcept;


        std::vector<Station_CRef>::const_iterator& From_Station(const Station& station) const noexcept;

    private:
        std::vector<Station_CRef> m_station_list;
        TimeTable m_schedule;
};

typedef std::reference_wrapper<const Schedule> Schedule_CRef;


#endif //SCHEDULE_H