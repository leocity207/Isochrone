#ifndef COORDINATE_H
#define COORDINATE_H

// STD
#include <utility>
#include <vector>
#include <type_traits>

// Utils
#include "includes/utils/ctor.h"


namespace Coordinate
{
	template<class T>
	class Base :public std::pair<T,T> 
	{
		static_assert(std::is_scalar<T>::value,"coordinate should be made of scalar type");
		//#####
		// CTOR
	public:
		DEFAULT_DEFAULT_CTOR(Base)
		DEFAULT_COPY(Base)
		DEFAULT_MOVE(Base)
		Base(T first,T second);

		//########
		// METHODS
	public:
		Base& operator+=(const Base& other);
		template<class E>
		Base& operator/=(E constant);

		//###############
		// STATIC METHODS
	public:
		/////////////////////////////////////////////////////
		/// Compute the barycenter of a vector of coordinate
		/// @param coordinates: list of coordinate
		/// @return           : the barycenter of the list coordiante
		static Base<T> Compute_Mean(std::vector<std::reference_wrapper<const Base<T>>>& coordinates) noexcept;
	};
} // Coordinate


#endif // COORDINATE_H
