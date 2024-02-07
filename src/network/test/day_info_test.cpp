#include "day_info_test.h"

#include "includes/network/day_info.h"

std::array<std::chrono::weekday, 7> weekdays = {
	std::chrono::Monday,
	std::chrono::Tuesday,
	std::chrono::Wednesday,
	std::chrono::Thursday,
	std::chrono::Friday,
	std::chrono::Saturday,
	std::chrono::Sunday
};

std::array<Network::DAY_TYPE, 3> day_Types = {
		Network::SCHOOL_DAYS,
		Network::VACATION_DAYS,
		Network::HOLYDAYS,
};



/////////////////////
/// Testing equality
/// TODO render combine
TEST_P(Day_Test, equality)
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

std::string Space_Triming_Test_Naming(testing::TestParamInfo<std::tuple<std::chrono::weekday, Network::DAY_TYPE>> id)
{
	switch (std::get<0>(id.param))
	{
	case std::chrono::Monday:
		return "Monday";
	case std::chrono::Tuesday:
		return "Tuesday";
	case std::chrono::Wednesday:
		return "Wednesday";
	case std::chrono::Thursday:
		return "Thursday";
	case std::chrono::Friday:
		return "Friday";
	case std::chrono::Saturday:
		return "Saturday";
	case std::chrono::Sunday:
		return "Saturday";
	default:
		throw "Unexpected index";
	}
}

INSTANTIATE_TEST_SUITE_P(
	test_days,
	Day_Test,
	::testing::Combine(
		::testing::ValuesIn(weekdays),
		::testing::ValuesIn(day_Types)),
	Space_Triming_Test_Naming
);


/////////////////////
/// Testing equality
/// TODO render combine
TEST_F(Day_Info_Test, Match)
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