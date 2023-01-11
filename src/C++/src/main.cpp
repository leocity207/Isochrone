#include "includes/utils/coordinate_2d.h"

#include "includes/network_optimizer/network.h"
#include "includes/algorithm/network_optimizer.h"

int main()
{
    std::setlocale(LC_ALL, "fr_FR.UTF-8");
    Network network("C:\\Users\\Leocl\\Documents\\Isochrone\\Ressource\\config.json");
    Sphere_Coordinate starting_coordinate("45°31'16.7\"N", "4°52'26.7\"E");
    double walking_speed = 2.5;
    Day day(std::chrono::Monday, SCHOOL_DAYS);
    DayTime starting_time(std::chrono::hours(7), std::chrono::minutes(0));
    Network_Optimizer optimizer(network, starting_coordinate, walking_speed, starting_time, day);
    auto optimized_station = optimizer.Optimize();
    return 0;
}