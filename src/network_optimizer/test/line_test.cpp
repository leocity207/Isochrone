#include "line_test.h"

#include "includes/network_optimizer/line.h"



TEST_F(Line_Test, Contain)
{
	Station A(Sphere_Coordinate(0, 0), "Station A");
	Station B(Sphere_Coordinate(0, 0), "Station B");
	Station C(Sphere_Coordinate(0, 0), "Station C");
	Station D(Sphere_Coordinate(0, 0), "Station D");

	std::vector<Station_CRef> ref_1 = { A,B,C,D };
	std::vector<Station_CRef> ref_2 = { A,B };
	TimeTable void_1;
	DayTemplate temp_1({ 0,1,1,1,1,1,0 }, { 1,1,1 });
	Schedule s_1(std::move(ref_1), std::move(void_1),std::move( temp_1));

	TimeTable void_2;
	DayTemplate temp_2({ 1,0,0,0,0,0,0}, { 1,1,1 });
	Schedule s_2(std::move(ref_2), std::move(void_2), std::move(temp_2));

	std::vector<Schedule> S;
	S.emplace_back(std::move(s_1));
	S.emplace_back(std::move(s_2));

	Line L(std::move(S), "Line 1");


	Day d(std::chrono::Monday, SCHOOL_DAYS);

	ASSERT_TRUE(L.Contain(A, d));
	ASSERT_TRUE(L.Contain(B, d));
	ASSERT_TRUE(L.Contain(C, d));
	ASSERT_TRUE(L.Contain(D, d));

	Day d_2(std::chrono::Sunday, SCHOOL_DAYS);

	ASSERT_TRUE(L.Contain(A, d_2));
	ASSERT_TRUE(L.Contain(B, d_2));
	ASSERT_FALSE(L.Contain(C, d_2));
	ASSERT_FALSE(L.Contain(D, d_2));
}