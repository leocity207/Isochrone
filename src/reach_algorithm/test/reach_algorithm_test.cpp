#include "reach_algorithm_test.h"

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


std::unique_ptr<Context::Scheduled_Network> Reach_Algorithm_Test::s_context;

void Reach_Algorithm_Test::SetUpTestSuite()
{
	std::filesystem::path path = std::string(RESOURCE_PATH()) + "config.json";
	auto [stations, scheduled_lines] = Resource::Archive::Plaine::Parse_Scheduled_Network_Resource(std::move(path));
	s_context = std::make_unique<Context::Scheduled_Network>(std::move(scheduled_lines),std::move(stations));
}

TEST_F(Reach_Algorithm_Test, test_with_normal_day)
{
	Context::Reach_Algorithm solver_context(*s_context, DayTime(hours(0), minutes(0)), 1, Sphere_Coordinate(0, 0), Network::Day(Monday, Network::SCHOOL_DAYS));
	Reach_Algorithm::Optimized algorithm;
	std::vector<Context::Station> result = solver_context.Optimize(algorithm);
	
	Context::Station a(s_context->Get_Station()[0], solver_context);
	Context::Station b(s_context->Get_Station()[1], solver_context);
	std::swap(a, b);
	int d = 1;
	int c = 2;
	std::swap(c, d);


	ASSERT_EQ(result[0].Get_Reaching_Time(), DayTime(hours(0),minutes(0)));
	ASSERT_EQ(result[1].Get_Reaching_Time(), DayTime(hours(0),minutes(2)));
	ASSERT_EQ(result[2].Get_Reaching_Time(), DayTime(hours(0),minutes(3)));
	ASSERT_EQ(result[3].Get_Reaching_Time(), DayTime(hours(0),minutes(3)));
	ASSERT_EQ(result[4].Get_Reaching_Time(), DayTime(hours(0),minutes(3)));
	ASSERT_EQ(result[5].Get_Reaching_Time(), DayTime(hours(0),minutes(3)));
}


TEST_F(Reach_Algorithm_Test, bypass)
{
	Context::Reach_Algorithm solver_context(*s_context, DayTime(hours(1), minutes(0)), 0.5, Sphere_Coordinate(0, 0), Network::Day(Monday, Network::SCHOOL_DAYS));
	Reach_Algorithm::Optimized algorithm;
	std::vector<Context::Station> result = solver_context.Optimize(algorithm);

	DayTime res = DayTime(hours(1), minutes(3)) + seconds((int)std::round(s_context->Get_Station()[3].Get_Distance_To(s_context->Get_Station()[4])));
	
	SCOPED_TRACE("Station A :" + Context::Station::Get_Station_By_Name(result, "Station A").Get_Reaching_Time().ToString() + " Expect " + DayTime(hours(1), minutes(0)).ToString() + "\n");
	SCOPED_TRACE("Station B :" + Context::Station::Get_Station_By_Name(result, "Station B").Get_Reaching_Time().ToString() + " Expect " + DayTime(hours(1), minutes(11)).ToString() + "\n");
	SCOPED_TRACE("Station C :" + Context::Station::Get_Station_By_Name(result, "Station C").Get_Reaching_Time().ToString() + " Expect " + DayTime(hours(1), minutes(16)).ToString() + "\n");
	SCOPED_TRACE("Station D :" + Context::Station::Get_Station_By_Name(result, "Station D").Get_Reaching_Time().ToString() + " Expect " + DayTime(hours(1), minutes(3)).ToString() + "\n");
	SCOPED_TRACE("Station E :" + Context::Station::Get_Station_By_Name(result, "Station E").Get_Reaching_Time().ToString() + " Expect " + res.ToString() + "\n");
	SCOPED_TRACE("Station F ;" + Context::Station::Get_Station_By_Name(result, "Station F").Get_Reaching_Time().ToString() + " Expect " + DayTime(hours(1), minutes(3)).ToString() + "\n");
	
	

	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station A").Get_Reaching_Time(), DayTime(hours(1),minutes(0)));
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station B").Get_Reaching_Time(), DayTime(hours(1),minutes(11)));
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station C").Get_Reaching_Time(), DayTime(hours(1),minutes(16)));
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station D").Get_Reaching_Time(), DayTime(hours(1),minutes(3)));
	
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station E").Get_Reaching_Time(), res);
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station F").Get_Reaching_Time(), DayTime(hours(1),minutes(3)));
}



TEST_F(Reach_Algorithm_Test, Get_Closest_Time_To_Station)
{
	DayTime start_time = DayTime(hours(20),minutes(0));
	Sphere_Coordinate start_coordinate(0, 0);
	Context::Reach_Algorithm solver_context(*s_context, std::move(start_time), 1, std::move(start_coordinate), Network::Day(Monday, Network::SCHOOL_DAYS));
	Reach_Algorithm::Optimized algorithm;
	std::vector<Context::Station> result = solver_context.Optimize(algorithm);

	DayTime res1 = start_time+seconds((int)std::round(s_context->Get_Station()[1].Get_Distance_To(start_coordinate)));
	DayTime res2 = start_time+seconds((int)std::round(s_context->Get_Station()[2].Get_Distance_To(start_coordinate)));
	DayTime res3 = start_time+seconds((int)std::round(s_context->Get_Station()[3].Get_Distance_To(start_coordinate)));
	DayTime res4 = start_time+seconds((int)std::round(s_context->Get_Station()[4].Get_Distance_To(start_coordinate)));
	DayTime res5 = start_time+seconds((int)std::round(s_context->Get_Station()[5].Get_Distance_To(start_coordinate)));

	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station A").Get_Reaching_Time(), start_time);
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station B").Get_Reaching_Time(), res1);
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station C").Get_Reaching_Time(), res2);
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station D").Get_Reaching_Time(), res3);
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station E").Get_Reaching_Time(), res4);
	ASSERT_EQ(Context::Station::Get_Station_By_Name(result, "Station F").Get_Reaching_Time(), res5);
}