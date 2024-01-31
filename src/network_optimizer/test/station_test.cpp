#include "station_test.h"

#include "includes/network_optimizer/station.h"

TEST_F(Station_Test,Equality)
{
	Sphere_Coordinate a(1,1);
	Sphere_Coordinate b(1,1);
	Station sa(std::move(a),"a");
	Station sb(std::move(b),"b");

	EXPECT_EQ(sa,sa);
	EXPECT_NE(sa,sb);
}