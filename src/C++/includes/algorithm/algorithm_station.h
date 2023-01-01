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
        Algorithm_Station(const Station* station_to_link,const Network_Optimizer* optimizer) noexcept;

        /////////////////////////////////////////////////////////////////////
        /// Give back the time you need to get from this station to the start
        DayTime Get_Best_Time_Start_To_Station() const noexcept;
        void Try_Set_New_Best_Time(DayTime& new_value);
        void Try_Set_New_Best_Time(std::optional<DayTime>& new_value);
        const DayTime& Get_Reach_Time() {return m_best_time;};


        /////////////////////////////////////
        /// Way to get the containing station
        const Station& Get() const noexcept;
        const Station& operator*() const noexcept;

        //should not move use station ID;
        bool operator<(const Algorithm_Station& other_station) const noexcept { return *m_ref_station < *other_station.m_ref_station; };

    private:
        Algorithm_Station() = delete;

        DayTime m_best_time;
        bool m_reach_by_transport;
        const Station* m_ref_station;
        const Network_Optimizer* m_optimizer;
};

#endif //ALGORITHM_STATION_H