#include "schedule_test.h"

// Network
#include "includes/network/schedule.h"

std::unique_ptr<Network::Schedule> Schedule_Test::s_schedule = nullptr;
std::vector<Network::Station> Schedule_Test::s_stations = std::vector<Network::Station>();
Network::TimeTable Schedule_Test::s_timetable;


void Schedule_Test::SetUpTestSuite()
{
	//monday and hollyday
	std::array<bool, 7> week_day_array = { 0,1,0,0,0,0,0 };
	std::array<bool, 3> day_type_array = { 0,0,1 };
	Network::DayTemplate temp = Network::DayTemplate(week_day_array, day_type_array);

	// Timetable Creation Aij (bellow representation is transposed)
	DayTime a00 = DayTime::From_Time_String("6:00").value() ; DayTime a10 = DayTime::From_Time_String("6:10").value() ;
	DayTime a01 = DayTime::From_Time_String("7:00").value() ; DayTime a11 = DayTime::From_Time_String("9:20").value() ;  DayTime a21 = DayTime::From_Time_String("9:40").value();
	DayTime a02 = DayTime::From_Time_String("9:20").value() ;                                                            DayTime a22 = DayTime::From_Time_String("9:50").value();
	DayTime a03 = DayTime::From_Time_String("10:10").value(); DayTime a13 = DayTime::From_Time_String("10:20").value(); DayTime a23 = DayTime::From_Time_String("10:30").value();
	DayTime a04 = DayTime::From_Time_String("12:00").value(); DayTime a14 = DayTime::From_Time_String("12:10").value();

	Network::TimeTable timetable = {
		{a00         ,a01,a02         ,a03,a04         },
		{a10         ,a11,std::nullopt,a13,a14         },
		{std::nullopt,a21,a22         ,a23,std::nullopt}};
	s_timetable = { 
		{a00         ,a01,a02         ,a03,a04         },
		{a10         ,a11,std::nullopt,a13,a14         },
		{std::nullopt,a21,a22         ,a23,std::nullopt}};

	Sphere_Coordinate coord1("45°38'13\"E", "45°32'13\"N");
	Sphere_Coordinate coord2("45°39'13\"E", "45°33'13\"N");
	Sphere_Coordinate coord3("45°34'13\"E", "45°33'13\"N");

	//Station fabrication
	s_stations.emplace_back(std::move(coord1), "Station 1");
	s_stations.emplace_back(std::move(coord2), "Station 2");
	s_stations.emplace_back(std::move(coord3), "Station 3");

	std::vector<Network::Station_CRef> station_list_ref(s_stations.begin(),s_stations.end());

	s_schedule = std::unique_ptr<Network::Schedule>(new Network::Schedule(std::move(station_list_ref), std::move(timetable), std::move(temp),"test"));
}

//////////////////////////////////////////////////////////////
/// if the start station or the end station is not in the list
/// if the start station is not in the same order as the end one we should return nullopt
TEST_F(Schedule_Test, Get_Time_To_Station_Wrong)
{
	Sphere_Coordinate coord("48°34'13\"E", "45°33'13\"N");
	Network::Station test(std::move(coord), "Station 4");

	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(test, test,DayTime(std::chrono::hours(7),std::chrono::minutes(4))).has_value());
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), test, DayTime(std::chrono::hours(7), std::chrono::minutes(4))).has_value());
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[1].get(), s_schedule->Get_Station_List()[0].get(), DayTime(std::chrono::hours(7), std::chrono::minutes(4))).has_value());
}

////////////////////////////////////////////////////////
/// get time between two station between at a given time
/// Three type of event can apear
///		- normal case when the next transport give you to the next station
///		- case when the next bus don't stop at your station (because the bus service is different during the day)
///		- there are no next bus since it's the end of the day
TEST_F(Schedule_Test, Expect_Value_Get_Time_To_Station)
{
	// normal case when its on the same line
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[1].get(), DayTime(std::chrono::hours(5), std::chrono::minutes(59))).value() , s_timetable[1][0].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[1].get(), DayTime(std::chrono::hours(5), std::chrono::minutes(59))).value() , s_timetable[1][0].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[2].get(), DayTime(std::chrono::hours(10),std::chrono::minutes(10))).value() , s_timetable[2][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[1].get(), s_schedule->Get_Station_List()[2].get(), DayTime(std::chrono::hours(10),std::chrono::minutes(10))).value() , s_timetable[2][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[1].get(), DayTime(std::chrono::hours(6), std::chrono::minutes(8))).value()  , s_timetable[1][1].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[2].get(), DayTime(std::chrono::hours(6), std::chrono::minutes(50))).value() , s_timetable[2][1].value());

	//hop to next line because of nullopt
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[1].get(), DayTime(std::chrono::hours(9), std::chrono::minutes(20))).value(), s_timetable[1][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[1].get(), DayTime(std::chrono::hours(7), std::chrono::minutes(30))).value(), s_timetable[1][3].value());
	EXPECT_EQ(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[2].get(), DayTime(std::chrono::hours(5), std::chrono::minutes(59))).value(), s_timetable[2][1].value());

	// case for the end of the day
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[2].get(), DayTime(std::chrono::hours(11), std::chrono::minutes(59))).has_value());
	EXPECT_FALSE(s_schedule->Get_Closest_Time_To_Station(s_schedule->Get_Station_List()[0].get(), s_schedule->Get_Station_List()[2].get(), DayTime(std::chrono::hours(15), std::chrono::minutes(59))).has_value());
}