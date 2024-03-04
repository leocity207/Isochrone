#include "includes/coordinate/sphere.h"

// STL
#include <cmath>
#include <numbers>

// Utils
#include "includes/utils/general.h"
#include "includes/utils/exception_def.h"

Coordinate::Spherical::Spherical(double longitude,double latitude) noexcept:
	Base<double>(latitude,longitude )
{
}

Coordinate::Spherical Coordinate::Spherical::From_String(const std::string_view& DMS_notation_1, const std::string_view& DMS_notation_2)

{
	double V1 = Generals::Parse_Angle(DMS_notation_1);
	double V2 = Generals::Parse_Angle(DMS_notation_2);

	if ((DMS_notation_1.back() == 'N' || DMS_notation_1.back() == 'S') && (DMS_notation_2.back() == 'E' || DMS_notation_2.back() == 'W'))
		return Spherical(V2, V1);
	else if ((DMS_notation_2.back() == 'N' || DMS_notation_2.back() == 'S') && (DMS_notation_1.back() == 'E' || DMS_notation_1.back() == 'W'))
		return Spherical(V1, V2);
	else
		THROW(ANGLE_BADLY_FORMATED);
}

double Coordinate::Spherical::Distance_To(const Spherical& other_coord) const noexcept
{
	double lat_diff = std::sin((other_coord.Latitude()-Latitude())*std::numbers::pi/360);
	double long_diff = std::sin((other_coord.Longitude() - Longitude())*std::numbers::pi/360);
	double prod = std::cos(other_coord.Latitude()*std::numbers::pi/180)*std::cos(Latitude()*std::numbers::pi/180);
	return 2*earth_radius*std::asin(std::sqrt(lat_diff*lat_diff+prod*long_diff*long_diff));
}

const double& Coordinate::Spherical::Latitude() const noexcept
{
	return first;
}

const double& Coordinate::Spherical::Longitude() const noexcept
{
	return second;
}

bool Coordinate::Spherical::operator==(const Coordinate::Spherical& other_coord) const noexcept
{
	return Latitude() == other_coord.Latitude() && Longitude() == other_coord.Longitude();
}
