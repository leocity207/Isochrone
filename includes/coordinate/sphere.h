#ifndef COORDINATE_SPHERICAL_H
#define COORDINATE_SPHERICAL_H

// STL
#include <string>

// Coordinate
#include "coordinate.h"


namespace Coordinate
{
	class Spherical : public Base<double>
	{
		////////
		/// CTOR
	public:
		DELETE_DEFAULT_CTOR(Spherical)
		DEFAULT_MOVE(Spherical)
		DEFAULT_COPY(Spherical)
		Spherical(double longitude, double latitude) noexcept;

		///////////
		/// METHODS
	public:
		double Distance_To(const Spherical&) const noexcept;
		const double& Latitude() const noexcept;
		const double& Longitude() const noexcept;
		bool operator==(const Spherical& other_coord) const noexcept;

		///////////////////
		/// STATIC METHODS
	public:
		/////////////////////////////////////////////////////////////////////////////////////////
		/// @brief contructor that parse two string of second minute degre
		/// @param DMS_notation_1 one of the two coordinate
		/// @param DMS_notation_2 one of the two coordinate
		/// @note if any of the string is badly formated we throw an error Bad_format_Coordinate
		static Spherical From_String(const std::string_view& DMS_notation_1, const std::string_view& DMS_notation_2);


		//////////////
		/// ATTRIBUTES
	public:
		static constexpr size_t earth_radius = 6378100;
	};
}// Coordinate


#endif //COORDINATE_SPHERICAL_H