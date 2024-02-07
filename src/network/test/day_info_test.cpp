#include "day_info_test.h"



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
	auto [weekday, day_Type] = GetParam();
	Network::Day day(weekday, day_Type);
	for(std::chrono::weekday weekday2 : weekdays)
		for (Network::DAY_TYPE day_type2 : day_Types)
		{
			Network::Day day2(weekday2, day_type2);
			if (day2 == day)
				EXPECT_EQ(day.Description(), day2.Description());
			else
			{
				EXPECT_NE(day.Description(), day2.Description());

				if (day2.GetDayType() == day.GetDayType())
					EXPECT_NE(day, day2);
				else
					EXPECT_NE(day, day2);

				if (day2.GetWeekday() == day.GetWeekday())
					EXPECT_NE(day, day2);
				else
					EXPECT_NE(day, day2);
			}
		}
}

std::string Space_Triming_Test_Naming(testing::TestParamInfo<std::tuple<std::chrono::weekday, Network::DAY_TYPE>> id)
{
	std::string str;
	switch (std::get<0>(id.param).c_encoding())
	{
	case std::chrono::Monday.c_encoding():
		str += "Monday"; break;
	case std::chrono::Tuesday.c_encoding():
		str += "Tuesday"; break;
	case std::chrono::Wednesday.c_encoding():
		str += "Wednesday"; break;
	case std::chrono::Thursday.c_encoding():
		str += "Thursday"; break;
	case std::chrono::Friday.c_encoding():
		str += "Friday"; break;
	case std::chrono::Saturday.c_encoding():
		str += "Saturday"; break;
	case std::chrono::Sunday.c_encoding():
		str += "Sunday"; break;
	default:
		throw "Unexpected index";
	}

	switch (std::get<1>(id.param))
	{
	case Network::SCHOOL_DAYS:
		str += "_Friday"; break;
	case Network::HOLYDAYS:
		str += "_Saturday"; break;
	case Network::VACATION_DAYS:
		str += "_Sunday"; break;
	default:
		throw "Unexpected index";
	}
	return str;
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
TEST_P(Day_Template_Test, Match)
{
	auto [su, m, tu, w, th, f, sa, school, vacation, holliday] = GetParam();

	std::array<bool, 7> week_day_array = { su,m,tu,w,th,f,sa};
	std::array<bool, 3> day_type_array = { school,vacation,holliday };
	Network::DayTemplate daytemplate = Network::DayTemplate(week_day_array, day_type_array);
	if (m)
	{
		if (school)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Monday, Network::SCHOOL_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Monday, Network::SCHOOL_DAYS)));

		if (vacation)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Monday, Network::VACATION_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Monday, Network::VACATION_DAYS)));

		if (holliday)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Monday, Network::HOLYDAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Monday, Network::HOLYDAYS)));
	}
	else
	{
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Monday, Network::SCHOOL_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Monday, Network::VACATION_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Monday, Network::HOLYDAYS)));
	}

	if (tu)
	{
		if (school)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Tuesday, Network::SCHOOL_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Tuesday, Network::SCHOOL_DAYS)));

		if (vacation)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Tuesday, Network::VACATION_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Tuesday, Network::VACATION_DAYS)));

		if (holliday)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Tuesday, Network::HOLYDAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Tuesday, Network::HOLYDAYS)));
	}
	else
	{
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Tuesday, Network::SCHOOL_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Tuesday, Network::VACATION_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Tuesday, Network::HOLYDAYS)));
	}

	if (w)
	{
		if (school)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Wednesday, Network::SCHOOL_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Wednesday, Network::SCHOOL_DAYS)));

		if (vacation)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Wednesday, Network::VACATION_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Wednesday, Network::VACATION_DAYS)));

		if (holliday)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Wednesday, Network::HOLYDAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Wednesday, Network::HOLYDAYS)));
	}
	else
	{
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Wednesday, Network::SCHOOL_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Wednesday, Network::VACATION_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Wednesday, Network::HOLYDAYS)));
	}

	if (th)
	{
		if (school)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Thursday, Network::SCHOOL_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Thursday, Network::SCHOOL_DAYS)));

		if (vacation)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Thursday, Network::VACATION_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Thursday, Network::VACATION_DAYS)));

		if (holliday)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Thursday, Network::HOLYDAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Thursday, Network::HOLYDAYS)));
	}
	else
	{
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Thursday, Network::SCHOOL_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Thursday, Network::VACATION_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Thursday, Network::HOLYDAYS)));
	}

	if (f)
	{
		if (school)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Friday, Network::SCHOOL_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Friday, Network::SCHOOL_DAYS)));

		if (vacation)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Friday, Network::VACATION_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Friday, Network::VACATION_DAYS)));

		if (holliday)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Friday, Network::HOLYDAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Friday, Network::HOLYDAYS)));
	}
	else
	{
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Friday, Network::SCHOOL_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Friday, Network::VACATION_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Friday, Network::HOLYDAYS)));
	}

	if (sa)
	{
		if (school)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)));

		if (vacation)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Saturday, Network::VACATION_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Saturday, Network::VACATION_DAYS)));

		if (holliday)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Saturday, Network::HOLYDAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Saturday, Network::HOLYDAYS)));
	}
	else
	{
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Saturday, Network::VACATION_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Saturday, Network::HOLYDAYS)));
	}

	if (su)
	{
		if (school)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Sunday, Network::SCHOOL_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Sunday, Network::SCHOOL_DAYS)));

		if (vacation)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Sunday, Network::VACATION_DAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Sunday, Network::VACATION_DAYS)));

		if (holliday)
			EXPECT_TRUE(daytemplate.Match(Network::Day(std::chrono::Sunday, Network::HOLYDAYS)));
		else
			EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Sunday, Network::HOLYDAYS)));
	}
	else
	{
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Sunday, Network::SCHOOL_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Sunday, Network::VACATION_DAYS)));
		EXPECT_FALSE(daytemplate.Match(Network::Day(std::chrono::Sunday, Network::HOLYDAYS)));
	}

	for (bool m2 : {true, false})
		for (bool tu2 : {true, false})
			for (bool w2 : {true, false})
				for (bool th2 : {true, false})
					for (bool f2 : {true, false})
						for (bool sa2 : {true, false})
							for (bool su2 : {true, false})
								for (bool school2 : {true, false})
									for (bool vacation2 : {true, false})
										for (bool holliday2 : {true, false})
										{
											std::array<bool, 7> week_day_array2 = { su2,m2,tu2,w2,th2,f2,sa2,};
											std::array<bool, 3> day_type_array2 = { school2,vacation2,holliday2 };
											Network::DayTemplate daytemplate2 = Network::DayTemplate(week_day_array2, day_type_array2);
											if (m == m2 && tu == tu2 && w == w2 && th == th2 && f == f2 && sa == sa2 && su == su2)
												EXPECT_EQ(daytemplate, daytemplate2);
											else
												EXPECT_NE(daytemplate, daytemplate2);
										}
}


std::string Space_Triming_Test_Naming_Day_Template(testing::TestParamInfo<std::tuple<bool, bool, bool, bool, bool, bool, bool, bool, bool, bool>> id)
{
	auto [m, tu, w, th, f, sa, su, school, vacation, holliday] = id.param;
	std::string str = "";
	str += m ? "mo" : "xx";
	str += "_";
	str += tu ? "tu" : "xx";
	str += "_";
	str += w ? "we" : "xx";
	str += "_";
	str += th ? "th" : "xx";
	str += "_";
	str += f ? "fr" : "xx";
	str += "_";
	str += sa ? "sa" : "xx";
	str += "_";
	str += su ? "su" : "xx";
	str += "___";
	str += school ? "sch" : "xxx";
	str += "_";
	str += vacation ? "vac" : "xxx";
	str += "_";
	str += holliday ? "hol" : "xxx";
	return str;
}

INSTANTIATE_TEST_SUITE_P(
	test_days,
	Day_Template_Test,
	::testing::Combine(
		::testing::ValuesIn({ true,false }),
		::testing::ValuesIn({ true,false }),
		::testing::ValuesIn({ true,false }),
		::testing::ValuesIn({ true,false }),
		::testing::ValuesIn({ true,false }),
		::testing::ValuesIn({ true,false }),
		::testing::ValuesIn({ true,false }),
		::testing::ValuesIn({ true,false }),
		::testing::ValuesIn({ true,false }),
		::testing::ValuesIn({ true,false })),
	Space_Triming_Test_Naming_Day_Template
);