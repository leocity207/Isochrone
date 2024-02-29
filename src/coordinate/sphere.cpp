#include "includes/coordinate/sphere.h"

// Utils
#include "includes/utils/general.h"
#include "includes/utils/exception_def.h"

// STL
#include <cmath>
#include <numbers>

Coordinate::Spherical::Spherical(double longitude,double latitude) noexcept:
	Base<double>(latitude,longitude ),
	m_latitude(first),
	m_longitude(second)
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
	double lat_diff = std::sin((other_coord.m_latitude-m_latitude)*std::numbers::pi/360);
	double long_diff = std::sin((other_coord.m_longitude-m_longitude)*std::numbers::pi/360);
	double prod = std::cos(other_coord.m_latitude*std::numbers::pi/180)*std::cos(m_latitude*std::numbers::pi/180);
	return 2*earth_radius*std::asin(std::sqrt(lat_diff*lat_diff+prod*long_diff*long_diff));
}

const double& Coordinate::Spherical::Get_Latitude() const noexcept
{
	return m_latitude;
}

const double& Coordinate::Spherical::Get_Longitude() const noexcept
{
	return m_longitude;
}
