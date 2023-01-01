#ifndef NETWORK_OPTIMIZER_H
#define NETWORK_OPTIMIZER_H

#include "includes/network_optimizer/network.h"
#include "algorithm_station.h"
#include "includes/utils/daytime.h"

class Network_Optimizer
{
public:
    Network_Optimizer() = delete;
    Network_Optimizer(const Network& network,const Sphere_Coordinate& start_coordinate,const double default_speed,const DayTime& start_time,const Day& day_type) noexcept;

    std::vector<Algorithm_Station> Optimize();
    
    const DayTime& Get_Start_Time() const noexcept {return m_start_time;};
    const double Get_Speed() const noexcept {return m_speed;};
    const Sphere_Coordinate& Get_Start_Coordinate() const noexcept {return m_start_coordinate;};

private:
    const DayTime& m_start_time;
    const double m_speed;
    const Sphere_Coordinate& m_start_coordinate;
    const Network& m_network;
    const Day& m_day_type;
};




#endif