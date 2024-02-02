#include "day_info_test.h"

#include "includes/network/day_info.h"



TEST_F(Day_Info_Test, day_test_equality)
{
	Network::Day a(std::chrono::Monday,   Network::HOLYDAYS);
	Network::Day b(std::chrono::Monday,   Network::HOLYDAYS);
	Network::Day c(std::chrono::Thursday, Network::HOLYDAYS);
	Network::Day d(std::chrono::Monday,   Network::SCHOOL_DAYS);

	ASSERT_EQ(a, b);

	ASSERT_NE(a, c);
	ASSERT_NE(a, d);
	ASSERT_NE(b, c);
	ASSERT_NE(b, d);
	ASSERT_NE(c, d);
}


TEST_F(Day_Info_Test, Day_Template_test)
{
	Network::Day a(std::chrono::Monday,   Network::HOLYDAYS);
	Network::Day b(std::chrono::Thursday, Network::HOLYDAYS);
	Network::Day c(std::chrono::Monday,   Network::SCHOOL_DAYS);
	Network::Day d(std::chrono::Thursday, Network::SCHOOL_DAYS);

	std::array<bool, 7> week_day_array = { 0,1,0,0,0,0,0 };
	std::array<bool, 3> day_type_array = { 0,0,1 };
	Network::DayTemplate temp = Network::DayTemplate(week_day_array, day_type_array);

	ASSERT_TRUE(temp.Match(a));
	ASSERT_FALSE(temp.Match(b));
	ASSERT_FALSE(temp.Match(d));
}