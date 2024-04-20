#ifndef COORDINATE_PLANAR_H
#define COORDINATE_PLANAR_H

// Coordinate
#include "coordinate.h"


namespace Coordinate
{
	namespace Projector { class Base; };
	class Spherical;

	///////////////////////////////////////////
	/// @brief  Represent 2D coordinate on a plan
	/// @tparam T a scalar
	/// @note   Default_constructible, copy_constructible, copy_assignable, move_constructible, move_asignable
	template<class T>
	class Planar : public Base<T>
	{
		//#####
		// CTOR
	public:
		DELETE_DEFAULT_CTOR(Planar)
		DEFAULT_MOVE(Planar)
		DEFAULT_COPY(Planar)

		///////////////////////////////
		/// @brief Explicit constructor
		Planar(T x,T y) noexcept;

		//////////////////////////////////////////////////////////////////////////////
		/// @note                    This construcor is only enabled if T is floating point
		/// @param sphere_coordinate The coordinate to derive from
		/// @param projector         The projector that will project the sphere point
		/// @throw                   "BAD_ANGULAR_VALUE_PROJECTION" if the sphere point cannot be projected
		Planar(const Spherical& sphere_coordinate,const Coordinate::Projector::Base& projector) requires std::is_floating_point<T>::value;

		//########
		// METHODS
	public:

		/////////////////////////////////////////////////////////////////////////
		/// @brief       Compute the ||.||_2 distance to another coordinate to the plan
		/// @param other Point to compute distance to
		/// @return      The distance between the two points
		double Distance_To(const Planar& other) const noexcept;

		//////////////////////////////////////
		/// @return The first part coordianate
		T X() const noexcept;

		/////////////////////////////////////////////
		/// @return The second part of the coordinate
		T Y() const noexcept;
	};
}


#endif //COORDINATE_PLANAR_H