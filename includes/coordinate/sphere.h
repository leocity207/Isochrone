#ifndef COORDINATE_SPHERICAL_H
#define COORDINATE_SPHERICAL_H

// STL
#include <string>

// Coordinate
#include "coordinate.h"


namespace Coordinate
{
	/////////////////////////////////////////////////////////////////////////////////
	/// @brief Represent 2D spherical coordinate in degree with longitude and latitude
	/// @note  default_constructible
	///        copy_constructible
	///        copy_assignable
	///        move_constructible
	///        move_asignable
	class Spherical : public Base<double>
	{
		//#####
		// CTOR
	public:
		DELETE_DEFAULT_CTOR(Spherical)
		DEFAULT_MOVE(Spherical)
		DEFAULT_COPY(Spherical)

		///////////////////////////////
		/// @brief Explicit constructor
		Spherical(double longitude, double latitude) noexcept;

		//########
		// METHODS
	public:
		/////////////////////////////////////////////////////////////////////////
		/// @brief       Compute the ||.||_2 non euclidian distance to another coordinate on the sphere
		/// @param other Point to compute distance to
		/// @return      The distance between the two points
		double Distance_To(const Spherical&) const noexcept;

		////////////////////////
		/// @return The Latitude
		const double& Latitude() const noexcept;

		/////////////////////////
		/// @return The Longitude
		const double& Longitude() const noexcept;

		///////////////////////////////////////
		/// @brief test if two coordinate are the same
		bool operator==(const Spherical& other_coord) const noexcept;

		//###############
		// STATIC METHODS
	public:
		/////////////////////////////////////////////////////////////////////////////////////////
		/// @brief                Contructor that parse two string of second minute degre
		/// @param DMS_notation_1 One of the two coordinate
		/// @param DMS_notation_2 One of the two coordinate
		/// @note                 If any of the string is badly formated we throw an error Bad_format_Coordinate
		static Spherical From_String(const std::string_view& DMS_notation_1, const std::string_view& DMS_notation_2);


		//############
		// ATTRIBUTES
	public:
		static constexpr size_t earth_radius = 6378100;
	};
}// Coordinate


#endif //COORDINATE_SPHERICAL_H