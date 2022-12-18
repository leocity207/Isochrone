#include "includes/algorithm/algorithm_station.h"


Algorithm_Station::Algorithm_Station(Sphere_Coordinate&& coordinate, std::string&& name) noexcept : Station(coordinate,name), m_best_time(0), m_reach_by_transport(false)
{

}
