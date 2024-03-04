#include "includes/coordinate/projector/base.h"

// Coordinate
#include "includes/coordinate/sphere.h"


Coordinate::Projector::Base::Base(Spherical&& mean_coordiante) noexcept :
	m_mean_coordinate(std::move(mean_coordiante))
{
}