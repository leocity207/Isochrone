#ifndef COORDINATE_H
#define COORDINATE_H

// STD
#include <utility>
#include <vector>
#include <type_traits>

// Utils
#include "includes/utils/ctor.h"

/////////////////////////////////////////////////////////////////////
/// @brief Coodinate represent 2D coordinate mainly a pair of numbers
namespace Coordinate
{
	//////////////////////////////////////////////
	/// @brief  Base clase for all coordinates
	/// @tparam T a scalar
	/// @note   Default_constructible
	///         copy_constructible
	///         copy_assignable
	///         move_constructible
	///         move_asignable
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

		///////////////////////////////
		/// @brief        Explicit constructor
		/// @param first  The first coordinate
		/// @param second The second coordinate
		Base(T first,T second);

		//########
		// METHODS
	public:
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief       Add the first element to the other first element and the second element to the other element
		/// @param other The other coordinate to add
		/// @return      (x1+x2,y1+y2)
		Base& operator+=(const Base& other);

		///////////////////////////////////////////////////////
		/// @brief          Divide the coordinate by a constant
		/// @tparam         Should be of scalar type
		/// @param constant The canstant to divid by
		/// @return         This coordinate with the dividend applyied
		template<class E>
		Base& operator/=(E constant);

		//###############
		// STATIC METHODS
	public:
		/////////////////////////////////////////////////////
		/// @brief             Compute the barycenter of a vector of coordinate
		/// @param coordinates List of coordinate
		/// @return            The barycenter of the list coordiante
		static Base<T> Compute_Mean(std::vector<std::reference_wrapper<const Base<T>>>& coordinates) noexcept;
	};
} // Coordinate


#endif // COORDINATE_H
