#ifndef COORDINATE_PROJECTOR_AZIMUTAL_EQUIDISTANTE_H
#define COORDINATE_PROJECTOR_AZIMUTAL_EQUIDISTANTE_H

// Projector
#include "base.h"


namespace Coordinate
{
	namespace Projector
	{
		class Azimuthal_Equidistant : public Base
		{
			////////
			// CTOR
		public:
			DELETE_DEFAULT_CTOR(Azimuthal_Equidistant)
			Azimuthal_Equidistant(Spherical&& mean_coordinate) noexcept;

			////////////
			/// METHDODS
		public:
			Planare_double Project(const Spherical& coordinate) const override;
		};
	}// Projection
}// Coordinate


#endif //COORDINATE_PROJECTOR_AZIMUTAL_EQUIDISTANTE_H