#include "includes/utils/planar_coordinate.h"
#include "includes/utils/sphere_coordinate.h"

#include <numbers>

#include "includes/Context/Scheduled_Network.h"

double Planar_Coordinate::s_mean_longitude_factor = 0.0;

Planar_Coordinate::Planar_Coordinate(const Sphere_Coordinate& other) noexcept:
	m_x(Sphere_Coordinate::earth_radius * other.Get_Lattitude() * std::numbers::pi/180.0),
	m_y(Sphere_Coordinate::earth_radius * other.Get_Longitude() * Planar_Coordinate::s_mean_longitude_factor* std::numbers::pi / 180.0)
{

}

void Planar_Coordinate::Compute_Mean_Longitude_Factor(const Context::Scheduled_Network& context)
{
	s_mean_longitude_factor = 0;
	for (const Network::Station& station : context.Get_Station())
		s_mean_longitude_factor += station.GetCoordinate().Get_Longitude();
	s_mean_longitude_factor /= context.Get_Station().size();
}


size_t Planar_Coordinate::Get_X() const noexcept
{
	return size_t();
}

size_t Planar_Coordinate::Get_Y() const noexcept
{
	return size_t();
}
