#include "schedule_test.h"

#include "includes/network/schedule.h"

#include "includes/utils/exception_def.h"

std::unique_ptr<Network::Schedule> Schedule_Test::s_schedule = nullptr;
std::vector<Network::Station> Schedule_Test::s_stations = std::vector<Network::Station>();

void Schedule_Test::SetUpTestSuite()
{
	//monday and hollyday
	std::array<bool, 7> week_day_array = { 0,1,0,0,0,0,0 };
	std::array<bool, 3> day_type_array = { 0,0,1 };
	Network::DayTemplate temp = Network::DayTemplate(week_day_array, day_type_array);

	// Timetable Creation
	DayTime a00 = DayTime::From_Time_String("10:10").value();
	DayTime a01 = DayTime::From_Time_String("9:20").value();

	DayTime a10 = DayTime::From_Time_String("10:20").value();
	DayTime a12 = DayTime::From_Time_String("9:20").value();

	DayTime a20 = DayTime::From_Time_String("10:30").value();
	DayTime a21 = DayTime::From_Time_String("9:20").value();

	Network::TimeTable timetable = { {a00,a01},{a10,a12},{a20,a21} };

	Sphere_Coordinate coord1("45°38'13\"E", "45°32'13\"N");
	Sphere_Coordinate coord2("45°39'13\"E", "45°33'13\"N");
	Sphere_Coordinate coord3("45°34'13\"E", "45°33'13\"N");

	//Station fabrication
	s_stations.emplace_back(std::move(coord1), "Station 1");
	s_stations.emplace_back(std::move(coord2), "Station 2");
	s_stations.emplace_back(std::move(coord3), "Station 3");

	std::vector<Network::Station_CRef> station_list_ref(s_stations.begin(),s_stations.end());

	s_schedule = std::unique_ptr<Network::Schedule>(new Network::Schedule(std::move(station_list_ref), std::move(timetable), std::move(temp)));
}

TEST_F(Schedule_Test, Contains_NotContains)
{
	Sphere_Coordinate coord("48°34'13\"E", "45°33'13\"N");
	Network::Station test(std::move(coord), "Station 4");

	ASSERT_FALSE(Schedule_Test::s_schedule->Contain(test));
}

TEST_F(Schedule_Test, Contains_Contains)
{
	for (Network::Station& gare :s_stations)
	{
		ASSERT_TRUE(Schedule_Test::s_schedule->Contain(gare));
	}
}

TEST_F(Schedule_Test, Get_Station_Index_Not_Contains)
{
	Sphere_Coordinate coord("48°34'13\"E", "45°33'13\"N");
	Network::Station test(std::move(coord), "Station 4");

	ASSERT_FALSE(Schedule_Test::s_schedule->Get_Station_Index(test).has_value());

}


TEST_F(Schedule_Test, Get_Station_Index_Contains)
{
	ASSERT_TRUE(Schedule_Test::s_schedule->Get_Station_Index(s_stations[0]).has_value());
	ASSERT_EQ(*Schedule_Test::s_schedule->Get_Station_Index(s_stations[0]),0);

	ASSERT_TRUE(Schedule_Test::s_schedule->Get_Station_Index(s_stations[1]).has_value());
	ASSERT_EQ(*Schedule_Test::s_schedule->Get_Station_Index(s_stations[1]), 1);

	ASSERT_TRUE(Schedule_Test::s_schedule->Get_Station_Index(s_stations[2]).has_value());
	ASSERT_EQ(*Schedule_Test::s_schedule->Get_Station_Index(s_stations[2]), 2);
}

TEST_F(Schedule_Test, Order_Throw)
{
	Sphere_Coordinate coord("48°34'13\"E", "45°33'13\"N");
	Network::Station test(std::move(coord), "Station 4");

	ASSERT_THROW(Schedule_Test::s_schedule->Order(test,s_stations[0]),STATION_NOT_IN_SCHEDULE);
	ASSERT_THROW(Schedule_Test::s_schedule->Order(test,test), STATION_NOT_IN_SCHEDULE);
	ASSERT_THROW(Schedule_Test::s_schedule->Order(s_stations[0],test), STATION_NOT_IN_SCHEDULE);

	ASSERT_THROW(Schedule_Test::s_schedule->Order(s_stations[0],s_stations[0]), CANNOT_ORDER_SAME_STATION);
	ASSERT_THROW(Schedule_Test::s_schedule->Order(s_stations[1],s_stations[1]), CANNOT_ORDER_SAME_STATION);
	ASSERT_THROW(Schedule_Test::s_schedule->Order(s_stations[2],s_stations[2]), CANNOT_ORDER_SAME_STATION);
}

TEST_F(Schedule_Test,Order_Normal)
{
	ASSERT_TRUE(Schedule_Test::s_schedule->Order(s_stations[0],s_stations[1]));
	ASSERT_TRUE(Schedule_Test::s_schedule->Order(s_stations[0],s_stations[2]));
	ASSERT_TRUE(Schedule_Test::s_schedule->Order(s_stations[1],s_stations[2]));

	ASSERT_FALSE(Schedule_Test::s_schedule->Order(s_stations[1],s_stations[0]));
	ASSERT_FALSE(Schedule_Test::s_schedule->Order(s_stations[2],s_stations[0]));
	ASSERT_FALSE(Schedule_Test::s_schedule->Order(s_stations[2],s_stations[1]));
}


TEST_F(Schedule_Test, Get_Station_list)
{
	const std::vector<Network::Station_CRef> station_list = s_schedule->Get_Station_List();
	ASSERT_EQ(station_list[0].get(),s_stations[0]);
	ASSERT_EQ(station_list[1].get(),s_stations[1]);
	ASSERT_EQ(station_list[2].get(),s_stations[2]);
}