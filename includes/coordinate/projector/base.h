#ifndef COORDINATE_PROJECTOR_BASE_H
#define COORDINATE_PROJECTOR_BASE_H

// Utils
#include "includes/utils/ctor.h"

// Coordinate
#include "includes/coordinate/sphere.h"

namespace Coordinate
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Projector represent spherical projection to planar transformation of 2D coordinate basicaly transforming a f(lattitude,longitude) = (x,y)
	/// @note not_default_constructible
	namespace Projector
	{
		using Planare_double = Coordinate::Base<double>;

		////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief base virtual class for projector every projectot inheritate this class
		/// @note not_default_constructible
		///       not_copy_constructible
		///       not_copy_assignable
		///       move_constructible
		///       move_asignable
		class Base
		{
			//#####
			// CTOR
		public:
			DELETE_DEFAULT_CTOR(Base)

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// @param mean_coordiante mean spherical coordinate used for the transformation since it is admited that f(x-E(x),y-E(y)) = (0,0)
			Base(Spherical&& mean_coordiante) noexcept;

			//########
			// METHODS
		public:
			////////////////////////////////////////////////////////
			/// @brief take a Spherical coordinate in input and transform it into a Planar coordinate
			/// @param coordinate a Spherical coordinate
			/// @return the planar equivalent of the spherical coordinate
			/// @throw "BAD_ANGULAR_VALUE_PROJECTION" for unsupported values of coordinate
			virtual Planare_double Project(const Spherical& coordinate) const = 0;

			//###########
			// ATTRIBUTES
		protected:
			Spherical m_mean_coordinate;
		};
	} // Projector
} // Coordinate


#endif //COORDINATE_PROJECTOR_BASE_H