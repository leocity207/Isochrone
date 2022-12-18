#include "includes/network_optimizer/station"
#include "includes/utils/coordinate_2d.h"



int main()
{
    Sphere_Coordinate coord = Sphere_Coordinate(0.0,0.0);
    Station a = Station(std::move(coord),"the station");

    return 0
}