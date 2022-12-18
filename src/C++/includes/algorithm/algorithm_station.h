#ifndef ALGORITHM_STATION_H
#define ALGORITHM_STATION_H

#include <chrono>

#include "includes/network_optimizer/station.h"
#include "includes/utils/coordinate_2d.h"
#include "includes/utils/daytime.h"

class Algorithm_Station: public Station 
{
    public:
        Algorithm_Station(Sphere_Coordinate&& coordinate, std::string&& name) noexcept;
        std::optional<DayTime> Get_Best_Time_Start_To_Station() const noexcept;
    private:
        Algorithm_Station() = delete;

        DayTime m_best_time;
        bool m_reach_by_transport;

};

#endif