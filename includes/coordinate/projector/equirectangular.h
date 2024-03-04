#ifndef COORDINATE_PROJECTOR_EQUIRECTANGULAR_H
#define COORDINATE_PROJECTOR_EQUIRECTANGULAR_H

// Projector
#include "base.h"


namespace Coordinate
{
	namespace Projector
	{
		class Equirectangular : public Base
		{
			////////
			// CTOR
		public:
			DELETE_DEFAULT_CTOR(Equirectangular)
			Equirectangular(Spherical&& mean_coordinate) noexcept;

			////////////
			/// METHDODS
		public:
			Planare_double Project(const Spherical& coordinate) const override;
		};
	}
}


#endif //COORDINATE_PROJECTOR_EQUIRECTANGULAR_H