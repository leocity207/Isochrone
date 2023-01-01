#ifndef LINE_H
#define LINE_H

#include <vector>

#include "includes/network_optimizer/schedule.h"
#include "submodule/Logger/includes/exception.h"
#include "includes/utils/exception_def.h"

#include <ranges>

class Algorithm_Station;



class Line
{
    private:
        std::string m_name;
        int m_id;
        std::vector<Schedule> m_schedule;
        static int s_count;
    public:
        Line() = delete;
        Line(std::vector<Schedule>&& Schedule,std::string&& name) noexcept;


        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Find the closest time to go from start to finish station knowing the curent daytime and the daytype
        /// @param start_station the station you want to get on 
        /// @param end_station the station you want to get out
        /// @param day_template a representation of the current day
        /// @return the arriving daytime at the end station. if no path were found it return an invalid daytime
        std::optional<DayTime_CRef> Get_Closest_Time_To_Station(const Algorithm_Station& start_station, const Station& end_station, const Day& day) const noexcept;

        /////////////////////////////////////////////////////////////////////////
        /// @brief Get the right schedule in the line following a paterne
        /// @param matching_day the day that should match with the schedule
        /// @param start_station the station that should be before the end station
        /// @param end_station the station that should be after the start station
        /// @note the start and end station are use to determinate the direction to use
        /// @return the right schedule if found, otherwise return a void schedule
        std::optional<Schedule_CRef> Get_Schedule(const Day& matching_day,const Station& start_station,const Station& end_station) const noexcept;

        auto Get_Schedules(const Day& matching_day) const noexcept
        {
            return std::views::filter(m_schedule, [matching_day](const Schedule& schedule) { return schedule.Match(matching_day); });
        };

        bool Contain(const Station& station,const Day& matching_day) const noexcept;
};

typedef std::reference_wrapper<Line> Line_CRef;

#endif //LINE_H