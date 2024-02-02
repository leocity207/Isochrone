#ifndef NETWORK_OPTIMIZER_H
#define NETWORK_OPTIMIZER_H

#include "includes/network/line.h"
#include "algorithm_station.h"
#include "includes/utils/daytime.h"

class Network_Optimizer
{
public:
    Network_Optimizer() = delete;
    Network_Optimizer(const std::vector<Network::Station>& stations, const std::vector<Network::Line>& lines,const Sphere_Coordinate& start_coordinate,const double default_speed,const DayTime& start_time,const Network::Day& day_type) noexcept;

    std::vector<Algorithm_Station> Optimize();
    
    const DayTime& Get_Start_Time() const noexcept;
    const double Get_Speed() const noexcept;
    const Sphere_Coordinate& Get_Start_Coordinate() const noexcept;

private:
    const DayTime& m_start_time;
    const double m_speed;
    const Sphere_Coordinate& m_start_coordinate;
    const std::vector<Network::Line>& m_lines;
    const std::vector<Network::Station>& m_stations;
    const Network::Day& m_day_type;
};


#endif