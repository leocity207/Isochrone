#include "station_test.h"

// Network
#include "includes/network/station.h"


//////////////////////////////////////////////////////////
/// test if two station are equal
/// two stations are equal only if their index is the same
TEST_F(Station_Test,Equality)
{
	Coordinate::Spherical a(1,1);

	Network::Station sa(std::move(a),"a");

	EXPECT_EQ(sa,sa);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// test if two station are not equal
/// two stations are equal only if their index is different not if their coordinate or name is same
TEST_F(Station_Test, Inequality)
{
	Coordinate::Spherical a(1, 1);
	Coordinate::Spherical b(1, 1);
	Coordinate::Spherical c(2, 2);
	Coordinate::Spherical d(1, 1);

	Network::Station sa(std::move(a), "a");
	Network::Station sb(std::move(b), "a");
	Network::Station sc(std::move(c), "a");
	Network::Station sd(std::move(d), "b");

	EXPECT_NE(sa, sb);
	EXPECT_NE(sa, sc);
	EXPECT_NE(sa, sd);
}

////////////////////////////////////////////////////////////////
/// Test if station is greater than another station
/// ordering for station is based on their index of construction
/// sa < sb < sc < sd
TEST_F(Station_Test, Greater)
{
	Coordinate::Spherical a(1, 1);
	Coordinate::Spherical b(1, 1);
	Coordinate::Spherical c(2, 2);
	Coordinate::Spherical d(1, 1);

	Network::Station sa(std::move(a), "a");
	Network::Station sb(std::move(b), "a");
	Network::Station sc(std::move(a), "a");
	Network::Station sd(std::move(b), "b");

	EXPECT_LT(sa, sb);
	EXPECT_LT(sa, sc);
	EXPECT_LT(sa, sd);

	EXPECT_LT(sb, sc);
	EXPECT_LT(sb, sd);

	EXPECT_LT(sc, sd);
}

//////////////////////////////////////////////////////
/// test the getter of a station
/// test if the get name give what we expect
/// test if the get coordinate gives us what we expect
TEST_F(Station_Test, Getter)
{
	Coordinate::Spherical a(1, 1);
	Coordinate::Spherical b(2, 2);

	Network::Station sa(std::move(a), "a");
	Network::Station sb(std::move(b), "b");

	EXPECT_EQ(sa.Get_Name(), "a");
	EXPECT_EQ(sb.Get_Name(), "b");

	EXPECT_EQ(sa.GetCoordinate(), Coordinate::Spherical(1,1));
	EXPECT_EQ(sb.GetCoordinate(), Coordinate::Spherical(2,2));
}

///////////////////////////////////////////////////////////////////////////
/// Test that the computation of distance to two station is correct
/// this give the straight distance to a station, not the track distance
TEST_F(Station_Test, distance_to)
{
	Coordinate::Spherical a(1, 1);
	Coordinate::Spherical b(2, 2);

	Network::Station sa(std::move(a), "a");
	Network::Station sb(std::move(b), "b");

	EXPECT_DOUBLE_EQ(sa.Get_Distance_To(sb), sa.Get_Distance_To(Coordinate::Spherical(2, 2)));
}