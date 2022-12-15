#include "includes/utils/coordinate_2d.h"

#include <cmath>
#include <numbers>

Sphere_Coordinate::Sphere_Coordinate(double longitude,double latitude) noexcept : m_longitude(longitude),m_latitude(latitude)
{

}

double Sphere_Coordinate::Get_Distance(const Sphere_Coordinate& other_coord) const
{
    double lat_diff = std::sin((other_coord.m_latitude-m_latitude)*std::numbers::pi/360);
    double long_diff = std::sin((other_coord.m_longitude-m_longitude)*std::numbers::pi/360);
    double prod = std::cos(other_coord.m_latitude*std::numbers::pi/180)*std::cos(m_latitude*std::numbers::pi/180);
    return 2*earth_radius*std::asin(std::sqrt(lat_diff*lat_diff+prod*long_diff*long_diff));
}