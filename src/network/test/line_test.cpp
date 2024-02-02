#include "line_test.h"

#include "includes/network/line.h"



TEST_F(Line_Test, Contain)
{
	Network::Station A(Sphere_Coordinate(0, 0), "Station A");
	Network::Station B(Sphere_Coordinate(0, 0), "Station B");
	Network::Station C(Sphere_Coordinate(0, 0), "Station C");
	Network::Station D(Sphere_Coordinate(0, 0), "Station D");

	std::vector<Network::Station_CRef> ref_1 = { A,B,C,D };
	std::vector<Network::Station_CRef> ref_2 = { A,B };
	Network::TimeTable void_1;
	Network::DayTemplate temp_1({ 0,1,1,1,1,1,0 }, { 1,1,1 });
	Network::Schedule s_1(std::move(ref_1), std::move(void_1),std::move( temp_1));

	Network::TimeTable void_2;
	Network::DayTemplate temp_2({ 1,0,0,0,0,0,0}, { 1,1,1 });
	Network::Schedule s_2(std::move(ref_2), std::move(void_2), std::move(temp_2));

	std::vector<Network::Schedule> S;
	S.emplace_back(std::move(s_1));
	S.emplace_back(std::move(s_2));

	Network::Line L(std::move(S), "Line 1");

	Network::Day d(std::chrono::Monday, Network::SCHOOL_DAYS);

	ASSERT_TRUE(L.Contain(A, d));
	ASSERT_TRUE(L.Contain(B, d));
	ASSERT_TRUE(L.Contain(C, d));
	ASSERT_TRUE(L.Contain(D, d));

	Network::Day d_2(std::chrono::Sunday, Network::SCHOOL_DAYS);

	ASSERT_TRUE(L.Contain(A, d_2));
	ASSERT_TRUE(L.Contain(B, d_2));
	ASSERT_FALSE(L.Contain(C, d_2));
	ASSERT_FALSE(L.Contain(D, d_2));
}