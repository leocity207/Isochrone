#include "includes/coordinate/projector/azimuthal_equidistant.h"

// STL
#include <numbers>
#include <cmath>

// Utils
#include "includes/utils/exception_def.h"


Coordinate::Projector::Azimuthal_Equidistant::Azimuthal_Equidistant(Coordinate::Spherical&& mean_coordinate) noexcept :
	Coordinate::Projector::Base(std::move(mean_coordinate))
{
}

#define ALMOST_ZERO(x) (x < 1e-15 ? 0 : x) 

Coordinate::Base<double> Coordinate::Projector::Azimuthal_Equidistant::Project(const Coordinate::Spherical& coordinate) const
{
	if(coordinate.Latitude() >= 180.0 || coordinate.Longitude() >= 180.0 || coordinate.Latitude() <= -180.0 || coordinate.Longitude() <= -180.0)
		THROW(BAD_ANGULAR_VALUE_PROJECTION)
	

	double phi = coordinate.Latitude() * std::numbers::pi / 180.0;
	double phi_0 = m_mean_coordinate.Latitude() * std::numbers::pi / 180.0;
	double lambda = coordinate.Longitude() * std::numbers::pi / 180.0;
	double lambda_0 = m_mean_coordinate.Longitude() * std::numbers::pi / 180.0;
	double cos_Rho_R = std::sin(phi_0) * std::sin(phi) + std::cos(phi_0) * std::cos(phi) * std::cos(lambda - lambda_0);
	double tan_theta_numerator = std::cos(phi) * std::sin(lambda - lambda_0);
	double tan_theta_denominator = std::cos(phi_0) * std::sin(phi) - std::sin(phi_0) * std::cos(phi) * std::cos(lambda - lambda_0);
	double theta;
	if (tan_theta_denominator == 0)
		if (coordinate == m_mean_coordinate)
			theta = 0;
		else
			theta = std::numbers::pi / 2;
	else
		theta = std::atan(tan_theta_numerator / tan_theta_denominator);
	double rho = std::acos(cos_Rho_R)  * Coordinate::Spherical::earth_radius;

	return Coordinate::Base<double>(rho * std::sin(theta), rho * std::cos(-theta));
	
	
	//double c = std::sin(phi_0) * std::sin(phi) + std::cos(phi_0) * std::cos(phi) * std::cos(lambda - lambda_0);
}
