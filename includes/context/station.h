#ifndef CONTEXT_REACHED_STATION_H
#define CONTEXT_REACHED_STATION_H

#include "includes/utils/ctor.h"
#include "includes/network/station.h"
#include "includes/utils/daytime.h"

#include <optional>

namespace Context
{
    //////////////////////////////////////////////////////////////////
    /// Class describing a station for the algorithm
    /// It hold the best time we arrive at this station
    /// It also hold extra information about how we reach the station
    class Station
    {
    
    ////////
    /// CTOR
    public:
        DELETE_COPY(Station);
        DELETE_DEFAULT(Station);
        DEFAULT_MOVE(Station);
        Station(const Network::Station& station_to_link,const Sphere_Coordinate& starting_Coordinate) noexcept;

        ////////////////////////////////////////////////////////////////////////////
        /// @brief Give back the time you need to get from this station to the start
        /// @return the daytime at which we reach the station
        DayTime Get_Best_Time_Start_To_Station() const noexcept;

        ///////////////////////////////////////////////////////////////////////////
        /// @brief try and see if the new daytime is better than the registered one
        /// @param new_value the new daytime value to reach the station where we want to see if better
        void Try_Set_New_Best_Time(DayTime& new_value);
        void Try_Set_New_Best_Time(std::optional<DayTime>& new_value);




        /////////////////////////////////////
        /// Way to get the containing station
        const Network::Station& Get() const noexcept;

        bool Is_Reach_Faster_Than(const Station& other_station) const noexcept;

        ///////////////////////////////
        /// give back the reaching time
        const DayTime& Get_Reach_Time()

        static const Station& Get_Station_By_Name(const std::vector<Algorithm_Station>& station_list, const std::string& name);

    private:
        Station() = delete;

        DayTime m_best_time;
        DayTime m_basic_time;
        bool m_reach_by_transport;
        const Network::Station& m_ref_station;
    };
}

#endif // !CONTEXT_REACHED_STATION_H
