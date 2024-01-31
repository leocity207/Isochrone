#include "coordinate_2d_test.h"

#include <string_view>

#include "includes/utils/coordinate_2d.h"
#include "includes/utils/exception_def.h"


TEST_F(Coordinate_Test,easy_constructor)
{
	Sphere_Coordinate a = Sphere_Coordinate(10, 10.0001);
	ASSERT_FLOAT_EQ(a.Get_Lattitude(), 10.0001);
	ASSERT_FLOAT_EQ(a.Get_Longitude(), 10.0);
}

TEST_F(Coordinate_Test, From_Double_String_Valid)
{
	Sphere_Coordinate a = Sphere_Coordinate("45°31'13\"E", "45°31'19.0\"N");
	ASSERT_FLOAT_EQ(a.Get_Lattitude(), 45.5219444444);
	ASSERT_FLOAT_EQ(a.Get_Longitude(), 45.5202777778);
}


TEST_F(Coordinate_Test, From_Double_String_Invalid)
{
	EXPECT_THROW(Sphere_Coordinate("45°31'13\"S", "45°31'19.0\"N"), ANGLE_BADLY_FORMATED);
}


TEST_F(Coordinate_Test, GetDistance_normal)
{
	Sphere_Coordinate a = Sphere_Coordinate(9, 9.992);
	Sphere_Coordinate b = Sphere_Coordinate(10.0001, 10.0004);

	ASSERT_FLOAT_EQ(a.Get_Distance(b), 109643.85);

}


TEST_F(Coordinate_Test, GetDistance_null)
{
	Sphere_Coordinate a = Sphere_Coordinate(0, 0);
	Sphere_Coordinate b = Sphere_Coordinate(0, 0);

	ASSERT_FLOAT_EQ(a.Get_Distance(b), 0.);
}