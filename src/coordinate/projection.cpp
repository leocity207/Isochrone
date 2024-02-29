#include "includes/coordinate/projection.h"
#include "includes/coordinate/sphere.h"

#include <type_traits>
#include <numbers>
#include <cmath>

Coordinate::Projection::Projection(Spherical&& mean_coordiante) noexcept :
	m_mean_coordinate(std::move(mean_coordiante))
{
}

Coordinate::Planare_double Coordinate::Equirectangular::Project(const Coordinate::Spherical& coordinate) const
{
	double x = Coordinate::Spherical::earth_radius * (coordinate.Get_Longitude() - m_mean_coordinate.Get_Longitude()) * std::numbers::pi / 180.0 * std::cos(coordinate.Get_Latitude() * std::numbers::pi / 180.0);
	double y = Coordinate::Spherical::earth_radius * (coordinate.Get_Latitude() - m_mean_coordinate.Get_Latitude()  ) * std::numbers::pi / 180.0;
	return Base<double>(x, y);
}

Coordinate::Planare_double Coordinate::Azimuthal_Equidistant::Project(const Coordinate::Spherical& coordinate) const
{
	double phi = coordinate.Get_Latitude() * std::numbers::pi / 180.0;
	double phi_0 = m_mean_coordinate.Get_Latitude() * std::numbers::pi / 180.0;
	double lambda = coordinate.Get_Longitude() * std::numbers::pi / 180.0;
	double lambda_0 = m_mean_coordinate.Get_Longitude() * std::numbers::pi / 180.0;
	double cos_Rho_R = std::sin(phi_0) * std::sin(phi) + std::cos(phi_0) * std::cos(phi)*(lambda - lambda_0);
	double tan_theta_numerator = std::cos(phi) * std::sin(lambda - lambda_0);
	double tan_theta_denominator = std::cos(phi) * std::sin(phi_0) - std::sin(phi_0) * std::cos(phi);

	double theta = std::atan(tan_theta_numerator / tan_theta_denominator);
	double rho = std::acos(cos_Rho_R) * Coordinate::Spherical::earth_radius;

	return Coordinate::Planare_double(rho * std::sin(theta), -rho * std::cos(theta));
}
