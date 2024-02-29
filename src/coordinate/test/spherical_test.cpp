#include "coordinate_2d_test.h"

// STL
#include <string_view>

// Utils
#include "includes/coordinate/sphere.h"
#include "includes/utils/exception_def.h"


TEST_F(Coordinate_Test,easy_constructor)
{
	Coordinate::Spherical a(10, 10.0001);
	EXPECT_DOUBLE_EQ(a.Get_Latitude(), 10.0001);
	EXPECT_DOUBLE_EQ(a.Get_Longitude(), 10.0);
}

TEST_F(Coordinate_Test, From_Double_String_Valid)
{
	Coordinate::Spherical a = Coordinate::Spherical::From_String("45°31'13\"E", "45°31'19.0\"N");
	EXPECT_DOUBLE_EQ(a.Get_Latitude(), 45.521944444444443);
	EXPECT_DOUBLE_EQ(a.Get_Longitude(), 45.520277777777778);
}

TEST_F(Coordinate_Test, From_Double_String_Invalid)
{
	EXPECT_THROW(Coordinate::Spherical::From_String("45°31'13\"S", "45°31'19.0\"N"), ANGLE_BADLY_FORMATED);
}

TEST_F(Coordinate_Test, GetDistance_normal)
{
	Coordinate::Spherical a(9, 9.992);
	Coordinate::Spherical b(10.0001, 10.0004);

	EXPECT_DOUBLE_EQ(a.Distance_To(b), 109643.85167255464);

}

TEST_F(Coordinate_Test, GetDistance_null)
{
	Coordinate::Spherical a(0, 0);
	Coordinate::Spherical b(0, 0);

	EXPECT_DOUBLE_EQ(a.Distance_To(b), 0.);
}