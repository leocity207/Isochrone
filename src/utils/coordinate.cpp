#include "includes/utils/coordinate_2d.h"

#include "includes/utils/general.h"
#include "includes/utils/exception_def.h"

#include <cmath>
#include <numbers>

Sphere_Coordinate::Sphere_Coordinate(double longitude,double latitude) noexcept : m_longitude(longitude),m_latitude(latitude)
{

}

Sphere_Coordinate::Sphere_Coordinate(const std::string_view& DMS_notation_1, const std::string_view& DMS_notation_2)
{
	double V1 = Generals::Parse_Angle(DMS_notation_1);
	double V2 = Generals::Parse_Angle(DMS_notation_2);

	if ((DMS_notation_1.back() == 'N' || DMS_notation_1.back() == 'S') && (DMS_notation_2.back() == 'E' || DMS_notation_2.back() == 'W'))
	{
		m_latitude = V1;
		m_longitude = V2;
	}
	else if ((DMS_notation_2.back() == 'N' || DMS_notation_2.back() == 'S') && (DMS_notation_1.back() == 'E' || DMS_notation_1.back() == 'W'))
	{
		m_latitude = V2;
		m_longitude = V1;
	}
	else
		THROW_TRACE(ANGLE_BADLY_FORMATED, "the two angles are of the sale type");
}

double Sphere_Coordinate::Get_Distance(const Sphere_Coordinate& other_coord) const
{
	double lat_diff = std::sin((other_coord.m_latitude-m_latitude)*std::numbers::pi/360);
	double long_diff = std::sin((other_coord.m_longitude-m_longitude)*std::numbers::pi/360);
	double prod = std::cos(other_coord.m_latitude*std::numbers::pi/180)*std::cos(m_latitude*std::numbers::pi/180);
	return 2*earth_radius*std::asin(std::sqrt(lat_diff*lat_diff+prod*long_diff*long_diff));
}


const double& Sphere_Coordinate::Get_Lattitude() const noexcept
{
	return m_latitude;
}

const double& Sphere_Coordinate::Get_Longitude() const noexcept
{
	return m_longitude;
}

bool Sphere_Coordinate::operator==(const Sphere_Coordinate& other_coord) const noexcept
{
	return m_latitude == other_coord.m_latitude && m_longitude == other_coord.m_longitude;
}
