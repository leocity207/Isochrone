#include "includes/utils/planar_coordinate.h"
#include "includes/utils/sphere_coordinate.h"

// STD
#include <numbers>
#include <cmath>
#include <vector>

double Planar_Coordinate::s_mean_longitude_factor = 0.0;
double Planar_Coordinate::s_mean_lattitude_factor = 0.0;


Planar_Coordinate::Planar_Coordinate(const Sphere_Coordinate& other) noexcept:
	m_x(Sphere_Coordinate::earth_radius * (other.Get_Lattitude() - s_mean_lattitude_factor) * std::numbers::pi/180.0),
	m_y(Sphere_Coordinate::earth_radius * (other.Get_Longitude() - s_mean_longitude_factor) * std::numbers::pi / 180.0)
{
}

Planar_Coordinate::Planar_Coordinate(double x, double y) noexcept :
	m_x(x),
	m_y(y)
{
}

void Planar_Coordinate::Compute_Mean_Factor(const std::vector<std::reference_wrapper<const Sphere_Coordinate>>& coordinates)
{
	s_mean_longitude_factor = 0;
	s_mean_lattitude_factor = 0;
	for (const Sphere_Coordinate& coordinate : coordinates)
	{
		s_mean_lattitude_factor += coordinate.Get_Lattitude();
		s_mean_longitude_factor += coordinate.Get_Longitude();
	}
	s_mean_longitude_factor /= coordinates.size();
	s_mean_lattitude_factor /= coordinates.size();
}

double Planar_Coordinate::Get_X() const noexcept
{
	return m_x;
}

double Planar_Coordinate::Get_Y() const noexcept
{
	return m_y;
}

double Planar_Coordinate::Get_Distance(const Planar_Coordinate& other) const noexcept
{
	return std::sqrt((other.m_x - m_x) * (other.m_x - m_x) + (other.m_y - m_y) * (other.m_y - m_y));
}