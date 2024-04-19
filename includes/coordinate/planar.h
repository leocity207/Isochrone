#ifndef COORDINATE_PLANAR_H
#define COORDINATE_PLANAR_H

// Coordinate
#include "coordinate.h"


namespace Coordinate
{
	namespace Projector { class Base; };
	class Spherical;

	template<class T>
	class Planar : public Base<T>
	{
		//#####
		// CTOR
	public:
		DELETE_DEFAULT_CTOR(Planar)
		DEFAULT_MOVE(Planar)
		DEFAULT_COPY(Planar)
		Planar(T x,T y) noexcept;

		//////////////////////////////////////////////////////////////////////////////
		/// @note This construcor is only enabled if T is floating point
		/// @param sphere_coordinate: the coordinate to derive from
		/// @param projector        : the projector that will project the sphere point
		/// @throw if the sphere point cannot be projected
		Planar(const Spherical& sphere_coordinate,const Coordinate::Projector::Base& projector) requires std::is_floating_point<T>::value;

		//########
		// METHODS
	public:
		double Distance_To(const Planar&) const noexcept;
		T X() const noexcept;
		T Y() const noexcept;
	};
}


#endif //COORDINATE_PLANAR_H