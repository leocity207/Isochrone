#ifndef COORDINATE_PROJECTOR_EQUIRECTANGULAR_H
#define COORDINATE_PROJECTOR_EQUIRECTANGULAR_H

// Projector
#include "base.h"


namespace Coordinate
{
	namespace Projector
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief represent Equirectangular projection https://en.wikipedia.org/wiki/Equirectangular_projection
		/// @note not_default_constructible
		///       not_copy_constructible
		///       not_copy_assignable
		///       move_constructible
		///       move_asignable
		class Equirectangular : public Base
		{
			//#####
			// CTOR
		public:
			DELETE_DEFAULT_CTOR(Equirectangular)

			////////////////////////////////////////////////////
			/// @brief Explicit constructor by move construction
			Equirectangular(Spherical&& mean_coordinate) noexcept;

			//#########
			// METHDODS
		public:
			Planare_double Project(const Spherical& coordinate) const override;
		};
	}
}


#endif //COORDINATE_PROJECTOR_EQUIRECTANGULAR_H