#ifndef ALGORITHM_STATION_H
#define ALGORITHM_STATION_H

#include <chrono>

#include "includes/network_optimizer/station.h"
#include "includes/utils/coordinate_2d.h"
#include "includes/utils/daytime.h"


//////////////////////////////////////////////////////////////////
/// Class describing a station for the algorithm
/// It hold the best time we arrive at this station
/// It also hold extra information about how we reach the station
class Algorithm_Station
{
    public:
        Algorithm_Station(const Station& station_to_link) noexcept;


        /////////////////////////////////////////////////////////////////////
        /// Give back the time you need to get from this station to the start
        std::optional<DayTime> Get_Best_Time_Start_To_Station() const noexcept;


        /////////////////////////////////////
        /// Way to get the containing station
        const Station& Get() const noexcept;
        const Station& operator*() const noexcept;

    private:
        Algorithm_Station() = delete;

        DayTime m_best_time;
        bool m_reach_by_transport;

        const Station& m_ref_station;
};

#endif //ALGORITHM_STATION_H