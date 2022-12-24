#include "day_info_test.h"

#include "includes/network_optimizer/day_info.h"



TEST_F(Day_Info_Test, day_test_equality)
{
	Day a = Day(std::chrono::Monday, HOLLY_DAY);
	Day b = Day(std::chrono::Monday, HOLLY_DAY);
	Day c = Day(std::chrono::Thursday, HOLLY_DAY);
	Day d = Day(std::chrono::Monday, SCHOOL_DAYS);

	ASSERT_EQ(a, b);

	ASSERT_NE(a, c);
	ASSERT_NE(a, d);
	ASSERT_NE(b, c);
	ASSERT_NE(b, d);
	ASSERT_NE(c, d);
}


TEST_F(Day_Info_Test, Day_Template_test)
{
	Day a = Day(std::chrono::Monday, HOLLY_DAY);
	Day b = Day(std::chrono::Thursday, HOLLY_DAY);
	Day c = Day(std::chrono::Monday, SCHOOL_DAYS);
	Day d = Day(std::chrono::Thursday, SCHOOL_DAYS);

	std::array<bool, 7> week_day_array = { 0,1,0,0,0,0,0 };
	std::array<bool, 3> day_type_array = { 0,0,1 };
	DayTemplate temp = DayTemplate(week_day_array, day_type_array);

	ASSERT_TRUE(temp.Match(a));
	ASSERT_FALSE(temp.Match(b));
	ASSERT_FALSE(temp.Match(d));
}