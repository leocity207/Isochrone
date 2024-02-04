#include "station_test.h"

#include "includes/network/station.h"

TEST_F(Station_Test,Equality)
{
	Sphere_Coordinate a(1,1);

	Network::Station sa(std::move(a),"a");

	EXPECT_EQ(sa,sa);
}

TEST_F(Station_Test, Inequality)
{
	Sphere_Coordinate a(1, 1);
	Sphere_Coordinate b(1, 1);
	Sphere_Coordinate c(2, 2);
	Sphere_Coordinate d(1, 1);

	Network::Station sa(std::move(a), "a");
	Network::Station sb(std::move(b), "a");
	Network::Station sc(std::move(c), "a");
	Network::Station sd(std::move(d), "b");

	EXPECT_NE(sa, sb);
	EXPECT_NE(sa, sc);
	EXPECT_NE(sa, sd);
}

TEST_F(Station_Test, Greater)
{
	Sphere_Coordinate a(1, 1);
	Sphere_Coordinate b(1, 1);
	Sphere_Coordinate c(2, 2);
	Sphere_Coordinate d(1, 1);

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

TEST_F(Station_Test, Getter)
{
	Sphere_Coordinate a(1, 1);
	Sphere_Coordinate b(2, 2);

	Network::Station sa(std::move(a), "a");
	Network::Station sb(std::move(b), "b");

	EXPECT_EQ(sa.Get_Name(), "a");
	EXPECT_EQ(sb.Get_Name(), "b");

	EXPECT_EQ(sa.GetCoordinate(), Sphere_Coordinate(1,1));
	EXPECT_EQ(sb.GetCoordinate(), Sphere_Coordinate(2,2));
}

TEST_F(Station_Test, distance_to)
{
	Sphere_Coordinate a(1, 1);
	Sphere_Coordinate b(2, 2);

	Network::Station sa(std::move(a), "a");
	Network::Station sb(std::move(b), "b");

	EXPECT_DOUBLE_EQ(sa.Get_Distance_To(sb), sa.Get_Distance_To(Sphere_Coordinate(2, 2)));
}