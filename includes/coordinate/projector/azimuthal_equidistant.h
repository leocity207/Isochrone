#ifndef COORDINATE_PROJECTOR_AZIMUTAL_EQUIDISTANTE_H
#define COORDINATE_PROJECTOR_AZIMUTAL_EQUIDISTANTE_H

// Projector
#include "base.h"


namespace Coordinate
{
	namespace Projector
	{
		///////////////////////////////////////////////
		/// @brief represent Azimuthal Equidistant projection https://en.wikipedia.org/wiki/Azimuthal_equidistant_projection
		/// @note not_default_constructible
		///       not_copy_constructible
		///       not_copy_assignable
		///       move_constructible
		///       move_asignable
		class Azimuthal_Equidistant : public Base
		{
			//#####
			// CTOR
		public:
			DELETE_DEFAULT_CTOR(Azimuthal_Equidistant)

			////////////////////////////////////////////////////
			/// @brief Explicit constructor by move construction
			Azimuthal_Equidistant(Spherical&& mean_coordinate) noexcept;

			//#########
			// METHDODS
		public:
			Planare_double Project(const Spherical& coordinate) const override;
		};
	}// Projection
}// Coordinate


#endif //COORDINATE_PROJECTOR_AZIMUTAL_EQUIDISTANTE_H