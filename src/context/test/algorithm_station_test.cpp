#include "algorithm_station_test.h"

#include "includes/network/schedule.h"
#include "config.h"

using namespace std::chrono;

#include "includes/resource/json/parser/resource_getter.h"
#include "includes/resource/csv/engine/file_parser.h"
#include "includes/resource/csv/parser/station.h"
#include "includes/resource/csv/parser/timetable.h"
#include "includes/context/Scheduled_Network.h"
#include "includes/resource/archive/plain.h"
#include "includes/context/reach_algorithm.h"
#include "includes/context/station.h"
#include "includes/reach_algorithm/optimized.h"


std::unique_ptr<Context::Scheduled_Network> Algorithm_Station_Test::s_context;

void Algorithm_Station_Test::SetUpTestSuite()
{
	std::filesystem::path path = std::string(RESOURCE_PATH()) + "config.json";
	auto [stations, scheduled_lines] = Resource::Archive::Plaine::Parse_Scheduled_Network_Resource(std::move(path));
	s_context = std::make_unique<Context::Scheduled_Network>(std::move(scheduled_lines), std::move(stations));
}

TEST_F(Algorithm_Station_Test, Get_Best_Time_Start_To_Station)
{
	DayTime start_time(hours(0), minutes(0));
	Context::Reach_Algorithm solver_context(*s_context, start_time, 1, Sphere_Coordinate(0, 0), Network::Day(Monday, Network::SCHOOL_DAYS));
	Reach_Algorithm::Optimized algorithm;
	std::vector<Context::Station> result = solver_context.Optimize(algorithm);

    Context::Station station_1(&(network.Get_Station()[0]),&optimizer);
	Context::Station station_2(&(network.Get_Station()[1]),&optimizer);
	Context::Station station_3(&(network.Get_Station()[2]),&optimizer);
	Context::Station station_4(&(network.Get_Station()[3]),&optimizer);
	Context::Station station_5(&(network.Get_Station()[4]),&optimizer);
	Context::Station station_6(&(network.Get_Station()[5]),&optimizer);

	


	DayTime res1 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[1])));
    DayTime res2 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[2])));
    DayTime res3 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[3])));
    DayTime res4 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[4])));
    DayTime res5 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[5])));

    ASSERT_EQ(station_1.Get_Best_Time_Start_To_Station(), start_time);
    ASSERT_EQ(station_2.Get_Best_Time_Start_To_Station(), res1);
    ASSERT_EQ(station_3.Get_Best_Time_Start_To_Station(), res2);
    ASSERT_EQ(station_4.Get_Best_Time_Start_To_Station(), res3);
    ASSERT_EQ(station_5.Get_Best_Time_Start_To_Station(), res4);
    ASSERT_EQ(station_6.Get_Best_Time_Start_To_Station(), res5);
}


TEST_F(Algorithm_Station_Test, Get_Closest_Time_To_Station)
{
    std::filesystem::path path = std::string(RESOURCE_PATH()) + "config.json";
    Network network(path);

	DayTime start_time(hours(0),minutes(0));
	Network::Day today(Monday,SCHOOL_DAYS);
    Network_Optimizer optimizer(network,Sphere_Coordinate(0,0),1,start_time,Day(Monday,SCHOOL_DAYS));
	const Line& line_1 = network.Get_Lines()[0];
	std::optional<Network::Schedule_CRef> Schedule_a = line_1.Get_Schedule(today,network.Get_Station()[0],network.Get_Station()[1]);
	std::optional<Network::Schedule_CRef> Schedule_r = line_1.Get_Schedule(today,network.Get_Station()[1],network.Get_Station()[0]);

	ASSERT_TRUE(Schedule_a.has_value());	
	ASSERT_TRUE(Schedule_r.has_value());

	const Network::Timetable& s_a = Schedule_a->get();
	const Network::Timetable& s_r = Schedule_r->get();

	Context::Station A(&(network.Get_Station()[0]),&optimizer);
	Context::Station C(&(network.Get_Station()[2]), &optimizer);
	std::optional<DayTime> value = s_a.Get_Closest_Time_To_Station(A,network.Get_Station()[1]);
	std::optional<DayTime> value_2 = s_r.Get_Closest_Time_To_Station(C,network.Get_Station()[1]);

	EXPECT_EQ(value.value(),DayTime(hours(0),minutes(2)));
	EXPECT_EQ(value_2.value(),DayTime(hours(18),minutes(35)));
}

TEST_F(Algorithm_Station_Test, Try_Set_Best_Time)
{
    std::filesystem::path path = std::string(RESOURCE_PATH()) + "config.json";
    Network network(path);

	DayTime start_time(hours(0),minutes(0));
	Day today(Monday,SCHOOL_DAYS);
    Network_Optimizer optimizer(network,Sphere_Coordinate(0,0),1,start_time,Day(Monday,SCHOOL_DAYS));
	Context::Station C(&(network.Get_Station()[2]),&optimizer);

	DayTime initial_reach_time = C.Get_Reach_Time();

	DayTime big(hours(10),minutes(0));
	C.Try_Set_New_Best_Time(big);

	//to big it shouldn't work
	ASSERT_EQ(C.Get_Reach_Time(), initial_reach_time);

	DayTime small(hours(0),minutes(0));
	C.Try_Set_New_Best_Time(small);

	//smaller so it's Okay
	ASSERT_EQ(C.Get_Reach_Time(), small);
}