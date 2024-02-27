#include "scheduled_line_test.h"

// Network
#include "includes/network/scheduled_line.h"

std::unique_ptr<Network::Scheduled_Line> Scheduled_Line_Test::s_schedule = nullptr;
std::vector<Network::Station> Scheduled_Line_Test::s_stations = std::vector<Network::Station>();
Network::TimeTable Scheduled_Line_Test::s_timetable;
Network::TimeTable Scheduled_Line_Test::s_timetable2;


void Scheduled_Line_Test::SetUpTestSuite()
{
	/////////////////////////
	/// Creating the stations
	Sphere_Coordinate coord1("45°38'13\"E", "45°32'13\"N");
	Sphere_Coordinate coord2("45°39'13\"E", "45°33'13\"N");
	Sphere_Coordinate coord3("45°34'13\"E", "45°33'13\"N");
	Sphere_Coordinate coord4("45°33'13\"E", "45°33'13\"N");

	//Station fabrication
	s_stations.emplace_back(std::move(coord1), "Station 1");
	s_stations.emplace_back(std::move(coord2), "Station 2");
	s_stations.emplace_back(std::move(coord3), "Station 3");
	s_stations.emplace_back(std::move(coord3), "Station 4");

	//////////////////////////////
	// Creating the first Schedule
	//monday and hollyday
	std::array<bool, 7> week_day_array = { 0,1,0,0,0,0,0 };
	std::array<bool, 3> day_type_array = { 0,0,1 };
	Network::DayTemplate temp = Network::DayTemplate(week_day_array, day_type_array);

	// Timetable Creation Aij (bellow representation is transposed)
	DayTime a00 = DayTime::From_Time_String("6:00").value() ; DayTime a10 = DayTime::From_Time_String("6:10").value() ;
	DayTime a01 = DayTime::From_Time_String("7:00").value() ; DayTime a11 = DayTime::From_Time_String("9:20").value() ; DayTime a21 = DayTime::From_Time_String("9:40").value();
	DayTime a02 = DayTime::From_Time_String("9:20").value() ;                                                           DayTime a22 = DayTime::From_Time_String("9:25").value();
	DayTime a03 = DayTime::From_Time_String("10:10").value(); DayTime a13 = DayTime::From_Time_String("10:20").value(); DayTime a23 = DayTime::From_Time_String("10:30").value();
	DayTime a04 = DayTime::From_Time_String("12:00").value(); DayTime a14 = DayTime::From_Time_String("12:10").value();

	Network::TimeTable timetable = {
		{a00         ,a01,a02         ,a03,a04         },
		{a10         ,a11,std::nullopt,a13,a14         },
		{std::nullopt,a21,a22         ,a23,std::nullopt}};
	s_timetable = { 
		{a00,a01,a02,a03,a04},
		{a10,a11,std::nullopt,a13,a14},
		{std::nullopt,a21,a22,a23,std::nullopt}};



	std::vector<Network::Station_CRef> station_list_ref(s_stations.begin(), s_stations.begin()+3);

	Network::Schedule schedule_1(std::move(station_list_ref), std::move(timetable), std::move(temp), "test");

	/////////////////////////////////////////////
	/// creating the second schedule
	/// weekend and hollyday schoold and vacation
	std::array<bool, 7> week_day_array2 = { 1,0,0,0,0,0,1 };
	std::array<bool, 3> day_type_array2 = { 1,1,1 };
	Network::DayTemplate temp2 = Network::DayTemplate(week_day_array2, day_type_array2);

	// Timetable Creation Aij (bellow representation is transposed)
	DayTime b00 = DayTime::From_Time_String("6:00").value() ; DayTime b10 = DayTime::From_Time_String("6:10").value() ;                                                         ; DayTime b30 = DayTime::From_Time_String("6:30").value() ;
	DayTime b01 = DayTime::From_Time_String("7:00").value() ; DayTime b11 = DayTime::From_Time_String("9:20").value() ; DayTime b21 = DayTime::From_Time_String("9:50").value() ; DayTime b31 = DayTime::From_Time_String("10:10").value();
	DayTime b02 = DayTime::From_Time_String("9:20").value() ;                                                            DayTime b22 = DayTime::From_Time_String("9:25").value(); DayTime b32 = DayTime::From_Time_String("9:40").value() ;
	DayTime b03 = DayTime::From_Time_String("10:10").value(); DayTime b13 = DayTime::From_Time_String("10:20").value(); DayTime b23 = DayTime::From_Time_String("10:30").value(); DayTime b33 = DayTime::From_Time_String("10:50").value();
	DayTime b04 = DayTime::From_Time_String("12:00").value(); DayTime b14 = DayTime::From_Time_String("12:10").value();

	Network::TimeTable timetable2 = {
		{b00         ,b01,b02         ,b03,b04         },
		{b10         ,b11,std::nullopt,b13,b14         },
		{std::nullopt,b21,b22         ,b23,std::nullopt},
		{b30         ,b31,b32         ,b33,std::nullopt}};
	s_timetable2 = {
		{b00         ,b01,b02         ,b03,b04         },
		{b10         ,b11,std::nullopt,b13,b14         },
		{std::nullopt,b21,b22         ,b23,std::nullopt},
		{b30         ,b31,b32         ,b33,std::nullopt}};

	std::vector<Network::Station_CRef> station_list_ref2(s_stations.begin(), s_stations.end());
	Network::Schedule schedule_2(std::move(station_list_ref2), std::move(timetable2), std::move(temp2), "test2");

	std::vector<Network::Schedule> schedules;
	schedules.emplace_back(std::move(schedule_1));
	schedules.emplace_back(std::move(schedule_2));
	Scheduled_Line_Test::s_schedule = std::make_unique<Network::Scheduled_Line>(std::move(schedules), "Scheduled line");
}


TEST_F(Scheduled_Line_Test, Get_Closest_Time_To_Station_monday_holiday)
{
	// test where station 4 does not exist
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[3], DayTime(std::chrono::hours(5), std::chrono::minutes(55)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).has_value());
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[2], s_stations[3], DayTime(std::chrono::hours(7), std::chrono::minutes(4)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).has_value());
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[1], s_stations[0], DayTime(std::chrono::hours(7), std::chrono::minutes(4)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).has_value());

	// normal case when its on the same line
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(5), std::chrono::minutes(59)),  Network::Day(std::chrono::Monday, Network::HOLYDAYS)).value(), s_timetable[1][0].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(5), std::chrono::minutes(59)),  Network::Day(std::chrono::Monday, Network::HOLYDAYS)).value(), s_timetable[1][0].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(10), std::chrono::minutes(10)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).value(), s_timetable[2][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[1], s_stations[2], DayTime(std::chrono::hours(10), std::chrono::minutes(10)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).value(), s_timetable[2][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(6), std::chrono::minutes(8)),   Network::Day(std::chrono::Monday, Network::HOLYDAYS)).value(), s_timetable[1][1].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(6), std::chrono::minutes(50)),  Network::Day(std::chrono::Monday, Network::HOLYDAYS)).value(), s_timetable[2][1].value());

	//hop to next line because of nullopt
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(9), std::chrono::minutes(20)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).value(), s_timetable[1][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(7), std::chrono::minutes(30)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).value(), s_timetable[1][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(5), std::chrono::minutes(59)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).value(), s_timetable[2][1].value());

	// case for the end of the day
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(11), std::chrono::minutes(59)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).has_value());
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(15), std::chrono::minutes(59)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).has_value());
}

TEST_F(Scheduled_Line_Test, Get_Closest_Time_To_Station_weekend_all)
{
	// this time station 4 does exist
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[3], DayTime(std::chrono::hours(5), std::chrono::minutes(55)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[3][0].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[2], s_stations[3], DayTime(std::chrono::hours(7), std::chrono::minutes(4)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[3][1].value());
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[1], s_stations[0], DayTime(std::chrono::hours(7), std::chrono::minutes(4)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).has_value());

	// normal case when its on the same line
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(5), std::chrono::minutes(59)),  Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[1][0].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(5), std::chrono::minutes(59)),  Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[1][0].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(10), std::chrono::minutes(10)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[2][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[1], s_stations[2], DayTime(std::chrono::hours(10), std::chrono::minutes(10)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[2][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(6), std::chrono::minutes(8)),   Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[1][1].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(6), std::chrono::minutes(50)),  Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[2][1].value());

	//hop to next line because of nullopt
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(9), std::chrono::minutes(20)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[1][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[1], DayTime(std::chrono::hours(7), std::chrono::minutes(30)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[1][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(5), std::chrono::minutes(59)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).value(), s_timetable2[2][1].value());

	// case for the end of the day
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(11), std::chrono::minutes(59)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).has_value());
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[2], DayTime(std::chrono::hours(15), std::chrono::minutes(59)), Network::Day(std::chrono::Saturday, Network::SCHOOL_DAYS)).has_value());
}

TEST_F(Scheduled_Line_Test, Get_Closest_Time_To_Station_Schedule_does_not_exist)
{
	//there are no Tuesday schedule
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[3], DayTime(std::chrono::hours(5), std::chrono::minutes(55)), Network::Day(std::chrono::Tuesday, Network::SCHOOL_DAYS)).has_value());
	//there are no monday schedule for schoolday
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[3], DayTime(std::chrono::hours(5), std::chrono::minutes(55)), Network::Day(std::chrono::Monday, Network::SCHOOL_DAYS)).has_value());
	//station 4 is not served on moday for holiday
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[3], DayTime(std::chrono::hours(5), std::chrono::minutes(55)), Network::Day(std::chrono::Monday, Network::HOLYDAYS)).has_value());
	//station 4 is served and exist at this hour on sunday for any daytype
	EXPECT_TRUE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[3], DayTime(std::chrono::hours(5), std::chrono::minutes(55)), Network::Day(std::chrono::Sunday, Network::SCHOOL_DAYS)).has_value());
	EXPECT_TRUE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[3], DayTime(std::chrono::hours(5), std::chrono::minutes(55)), Network::Day(std::chrono::Sunday, Network::VACATION_DAYS)).has_value());
	EXPECT_TRUE(s_schedule->Get_Closest_Time_To_Station(s_stations[0], s_stations[3], DayTime(std::chrono::hours(5), std::chrono::minutes(55)), Network::Day(std::chrono::Sunday, Network::HOLYDAYS)).has_value());
}

TEST_F(Scheduled_Line_Test, Get_Schedule)
{
	for (std::chrono::weekday day : {std::chrono::Monday, std::chrono::Tuesday, std::chrono::Wednesday, std::chrono::Thursday, std::chrono::Friday, std::chrono::Saturday, std::chrono::Sunday})
		for (Network::DAY_TYPE type : {Network::SCHOOL_DAYS, Network::VACATION_DAYS, Network::HOLYDAYS})
		{
			if (day == std::chrono::Monday && type == Network::HOLYDAYS)
			{
				EXPECT_TRUE(s_schedule->Get_Schedule(Network::Day(day, type), s_stations[0], s_stations[1]).has_value());
				EXPECT_FALSE(s_schedule->Get_Schedule(Network::Day(day, type), s_stations[0], s_stations[3]).has_value());
			}
			else if ((day == std::chrono::Saturday || day == std::chrono::Sunday))
			{
				EXPECT_TRUE(s_schedule->Get_Schedule(Network::Day(day, type), s_stations[0], s_stations[1]).has_value());
				EXPECT_TRUE(s_schedule->Get_Schedule(Network::Day(day, type), s_stations[0], s_stations[3]).has_value());
			}
			else
			{
				EXPECT_FALSE(s_schedule->Get_Schedule(Network::Day(day, type), s_stations[0], s_stations[1]).has_value());
				EXPECT_FALSE(s_schedule->Get_Schedule(Network::Day(day, type), s_stations[0], s_stations[3]).has_value());
			}
		}
}

TEST_F(Scheduled_Line_Test, Get_Schedules)
{

	for (std::chrono::weekday day : {std::chrono::Monday, std::chrono::Tuesday, std::chrono::Wednesday, std::chrono::Thursday, std::chrono::Friday, std::chrono::Saturday, std::chrono::Sunday})
		for (Network::DAY_TYPE type : {Network::SCHOOL_DAYS, Network::VACATION_DAYS, Network::HOLYDAYS})
		{
			int i = 0;
			for (const auto& temp : s_schedule->Get_Schedules(Network::Day(day, type)))
			{
				temp.Get_Station_List();
				i++;
			}

			if (day == std::chrono::Monday && type == Network::HOLYDAYS)
				EXPECT_EQ(i, 1);
			else if ((day == std::chrono::Saturday || day == std::chrono::Sunday))
				EXPECT_EQ(i, 1);
			else
				EXPECT_EQ(i, 0);
		}
}

TEST_F(Scheduled_Line_Test, Contain)
{
	for (std::chrono::weekday day : {std::chrono::Monday, std::chrono::Tuesday, std::chrono::Wednesday, std::chrono::Thursday, std::chrono::Friday, std::chrono::Saturday, std::chrono::Sunday})
		for (Network::DAY_TYPE type : {Network::SCHOOL_DAYS, Network::VACATION_DAYS, Network::HOLYDAYS})
		{
			if (day == std::chrono::Monday && type == Network::HOLYDAYS)
			{
				EXPECT_TRUE(s_schedule->Contain(s_stations[0],  Network::Day(day, type)));
				EXPECT_TRUE(s_schedule->Contain(s_stations[1],  Network::Day(day, type)));
				EXPECT_TRUE(s_schedule->Contain(s_stations[2],  Network::Day(day, type)));
				EXPECT_FALSE(s_schedule->Contain(s_stations[3], Network::Day(day, type)));
			}
			else if ((day == std::chrono::Saturday || day == std::chrono::Sunday))
			{
				EXPECT_TRUE(s_schedule->Contain(s_stations[0], Network::Day(day, type)));
				EXPECT_TRUE(s_schedule->Contain(s_stations[1], Network::Day(day, type)));
				EXPECT_TRUE(s_schedule->Contain(s_stations[2], Network::Day(day, type)));
				EXPECT_TRUE(s_schedule->Contain(s_stations[3], Network::Day(day, type)));
			}
			else
			{
				EXPECT_FALSE(s_schedule->Contain(s_stations[0], Network::Day(day, type)));
				EXPECT_FALSE(s_schedule->Contain(s_stations[1], Network::Day(day, type)));
				EXPECT_FALSE(s_schedule->Contain(s_stations[2], Network::Day(day, type)));
				EXPECT_FALSE(s_schedule->Contain(s_stations[3], Network::Day(day, type)));
			}
		}
}