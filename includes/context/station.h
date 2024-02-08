#ifndef CONTEXT_REACHED_STATION_H
#define CONTEXT_REACHED_STATION_H

//std
#include <optional>

//utils
#include "includes/utils/ctor.h"
#include "includes/utils/daytime.h"

//network
#include "includes/network/station.h"


namespace Context
{
    class Reach_Algorithm;
    //////////////////////////////////////////////////////////////////
    /// Class describing a station for the algorithm
    /// It hold the best time we arrive at this station
    /// It also hold extra information about how we reach the station
    class Station
    {
    
    ////////
    /// CTOR
    public:
        DELETE_DEFAULT(Station);
        DELETE_COPY(Station);
        DEFAULT_MOVE(Station);

        Station(const Network::Station& station_to_link,const Reach_Algorithm& reach_algorithm_context) noexcept;

    ///////////
    /// METHODS
    public:
        ////////////////////////////////////////////////////////////////////////////
        /// @brief Give back the time you need to get from this station to the start
        /// @return the daytime at which we reach the station
        const DayTime& Get_Reaching_Time() const noexcept;

        ///////////////////////////////////////////////////////////////////////////
        /// @brief try and see if the new daytime is better than the registered one
        /// @param new_value the new daytime value to reach the station where we want to see if better
        void Try_Set_New_Best_Time(DayTime& new_value);
        void Try_Set_New_Best_Time(std::optional<DayTime>& new_value);

        /////////////////////////////////////
        /// Way to get the containing station
        const Network::Station& Get() const noexcept;

        bool operator<(const Context::Station &other_station) const noexcept;

        static const Station& Get_Station_By_Name(const std::vector<Station>& station_list, const std::string& name);

    //////////////
    /// ATTRIBUTES
    private:
        DayTime m_best_time;
        DayTime m_basic_time;
        bool m_reach_by_transport;
        std::reference_wrapper<const Network::Station> m_ref_station;
    };

    
}

#endif // !CONTEXT_REACHED_STATION_H