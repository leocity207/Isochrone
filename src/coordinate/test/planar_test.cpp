#include "planar_test.h"

// STL
#include <string_view>

// Coordinate
#include "includes/coordinate/planar.h"


TEST_F(Planar_Test,easy_constructor)
{
	Coordinate::Planar<double> a(10, 10.0001);
	EXPECT_DOUBLE_EQ(a.Y(), 10.0001);
	EXPECT_DOUBLE_EQ(a.X(), 10.0);
}

TEST_F(Planar_Test, GetDistance_normal)
{
	{
		Coordinate::Planar<size_t> a(1, 0);
		Coordinate::Planar<size_t> b(0, 1);

		EXPECT_DOUBLE_EQ(a.Distance_To(b), std::sqrt(2));
	}
	{
		Coordinate::Planar<double> a(1, 0);
		Coordinate::Planar<double> b(0, 1);

		EXPECT_DOUBLE_EQ(a.Distance_To(b), std::sqrt(2));
	}
	{
		Coordinate::Planar<int> a(1, 0);
		Coordinate::Planar<int> b(0, 1);

		EXPECT_DOUBLE_EQ(a.Distance_To(b), std::sqrt(2));
	}
}

TEST_F(Planar_Test, GetDistance_null)
{
	{
		Coordinate::Planar<int> a(1000, 1000);
		Coordinate::Planar<int> b(1000, 1000);

		EXPECT_DOUBLE_EQ(a.Distance_To(b), 0);
	}
	{
		Coordinate::Planar<double> a(1000, 1000);
		Coordinate::Planar<double> b(1000, 1000);

		EXPECT_DOUBLE_EQ(a.Distance_To(b), 0);
	}
	{
		Coordinate::Planar<size_t> a(1000, 1000);
		Coordinate::Planar<size_t> b(1000, 1000);

		EXPECT_DOUBLE_EQ(a.Distance_To(b), 0);
	}
}