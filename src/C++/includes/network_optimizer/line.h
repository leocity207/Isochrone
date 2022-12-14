#ifndef LINE_H
#define LINE_H

#include <vector>

#include "includes/network_optimizer/schedule.h"
#include "submodule/Logger/includes/exception.h"

DECLARE_EXCEPTION(Exception,Station_Not_In_Line,"One of the station is not in the current line.");
DECLARE_EXCEPTION(Exception,No_Matching_Schedule,"No Schedule was found for the day");

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
        /// @param current_time the time at wich you start waiting at the start station
        /// @param day_template a representation of the current day
        /// @return the arriving daytime at the end station. if no path were found it return an invalid daytime
        DayTime& Get_Closest_Time_To_Station(const Station& start_station,const Station& end_station,const DayTime& current_time,const Day& day) const;

        ////////////////////////////////////////////////////////////////////////////
        /// @brief Check if the Line contain a Station for the specified day
        /// @param station_to_find the station to check if it's in line
        /// @param day the day you want to do your research 
        /// @return wether or not the line contain the station at the specified day
        bool Contain(const Station& station_to_find,const Day& day) noexcept(false) const;

        /////////////////////////////////////////////////////////////////////////
        /// @brief Get the right schedule in the line following a paterne
        /// @param matching_day the day that should match with the schedule
        /// @param start_station the station that should be before the end station
        /// @param end_station the station that should be after the start station
        /// @note the start and end station are use to determinate the direction to use
        /// @return the right schedule if found, otherwise return a void schedule
        const Schedule& Get_Schedule(const Day& matching_day,const Station& start_station,const Station& end_station) noexcept(false) const;
        

    
};

#endif //LINE_H