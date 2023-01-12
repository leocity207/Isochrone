#ifndef ALGORITHM_STATION_H
#define ALGORITHM_STATION_H

#include <chrono>

#include "includes/network_optimizer/station.h"
#include "includes/utils/coordinate_2d.h"
#include "includes/utils/daytime.h"

class Network_Optimizer;

//////////////////////////////////////////////////////////////////
/// Class describing a station for the algorithm
/// It hold the best time we arrive at this station
/// It also hold extra information about how we reach the station
class Algorithm_Station
{
    public:
        Algorithm_Station(const Station& station_to_link,const Network_Optimizer& optimizer,std::list<Algorithm_Station>::iterator& pos) noexcept;

        ////////////////////////////////////////////////////////////////////////////
        /// @brief Give back the time you need to get from this station to the start
        /// @return the daytime at which we reach the station
        DayTime Get_Reach_Time() const noexcept;

        ///////////////////////////////////////////////////////////////////////////
        /// @brief try and see if the new daytime is better than the registered one
        /// @param new_value the new daytime value to reach the station where we want to see if better
        bool Try_Set_New_Best_Time_Transport(DayTime& new_value);
        bool Try_Set_New_Best_Time_Transport(std::optional<DayTime>& new_value);
        bool Try_Set_New_Best_Time_Base(DayTime& new_value);
        bool Try_Set_New_Best_Time_Base(std::optional<DayTime>& new_value);

        bool Has_Been_Reached_By_Transport();
        bool Has_Been_Reached_Once_By_Transport();
        
        /////////////////////////////////////
        /// Way to get the containing station
        const Station& Get() const noexcept;
        std::list<Algorithm_Station>::iterator& Get_Pos() const noexcept;


        bool operator<(const Algorithm_Station& other_station) const noexcept;

        ///////////////////////////////
        /// give back the reaching time
        const DayTime& Get_Reach_Time() {return m_best_time;};

        static const Algorithm_Station& Get_Station_By_Name(const std::vector<Algorithm_Station>& station_list, const std::string& name);

    private:
        Algorithm_Station() = delete;

        DayTime m_best_time;
        bool m_reach_by_transport;
        std::reference_wrapper<const Station> m_linked_station;
        bool m_reach_by_transport_once;
        std::reference_wrapper<std::list<Algorithm_Station>::iterator> m_pos;
};

#endif //ALGORITHM_STATION_H