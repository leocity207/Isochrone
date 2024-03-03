#ifndef COORDINATE_PROJECTOR_BASE_H
#define COORDINATE_PROJECTOR_BASE_H

// Utils
#include "includes/utils/ctor.h"

// Coordinate
#include "includes/coordinate/sphere.h"

namespace Coordinate
{
	namespace Projector
	{
		using Planare_double = Coordinate::Base<double>;

		class Base
		{
			////////
			/// CTOR
		public:
			DELETE_DEFAULT_CTOR(Base)
			Base(Spherical&& mean_coordiante) noexcept;

			////////////
			/// METHODS
		public:
			virtual Planare_double Project(const Spherical& coordinate) const = 0;

			//////////////
			/// ATTRIBUTES
		protected:
			Spherical m_mean_coordinate;
		};
	} // Projector
} // Coordinate

#endif //COORDINATE_PROJECTOR_BASE_H