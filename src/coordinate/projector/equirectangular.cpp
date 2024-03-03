#include "includes/coordinate/projector/equirectangular.h"

#include <type_traits>
#include <numbers>

#include "includes/utils/exception_def.h"

Coordinate::Projector::Equirectangular::Equirectangular(Coordinate::Spherical&& mean_coordinate) noexcept :
	Coordinate::Projector::Base(std::move(mean_coordinate))
{
}


Coordinate::Base<double> Coordinate::Projector::Equirectangular::Project(const Coordinate::Spherical& coordinate) const
{
	if (coordinate.Latitude() >= 180.0 || coordinate.Longitude() >= 180.0 || coordinate.Latitude() <= -180.0 || coordinate.Longitude() <= -180.0)
		THROW(BAD_ANGULAR_VALUE_PROJECTION)
	double x = Coordinate::Spherical::earth_radius * (coordinate.Longitude() - m_mean_coordinate.Longitude()) * std::numbers::pi / 180.0 * std::cos(m_mean_coordinate.Latitude() * std::numbers::pi / 180.0);
	double y = Coordinate::Spherical::earth_radius * (coordinate.Latitude() - m_mean_coordinate.Latitude()) * std::numbers::pi / 180.0;
	return Coordinate::Base<double>(x, y);
}
