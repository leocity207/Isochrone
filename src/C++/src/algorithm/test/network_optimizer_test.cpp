#include "network_optimizer_test.h"

#include "includes/algorithm/network_optimizer.h"

using namespace std::chrono;


TEST_F(Network_Optimizer_Test, test_with_normal_day)
{
    std::filesystem::path path = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/algorithm/test/resource_test/config.json";
    Network network(path);
    Network_Optimizer optimizer(network, Sphere_Coordinate(0, 0), 1, DayTime(hours(0), minutes(0)), Day(Monday, SCHOOL_DAYS));
    std::vector<Algorithm_Station> result = optimizer.Optimize();

    ASSERT_EQ(result[0].Get_Reach_Time(), DayTime(hours(0), minutes(0)));
    ASSERT_EQ(result[1].Get_Reach_Time(), DayTime(hours(0), minutes(2)));
    ASSERT_EQ(result[2].Get_Reach_Time(), DayTime(hours(0), minutes(3)));
    ASSERT_EQ(result[3].Get_Reach_Time(), DayTime(hours(0), minutes(3)));
    ASSERT_EQ(result[4].Get_Reach_Time(), DayTime(hours(0), minutes(3)));
    ASSERT_EQ(result[5].Get_Reach_Time(), DayTime(hours(0), minutes(3)));
}


TEST_F(Network_Optimizer_Test, bypass)
{
    std::filesystem::path path = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/algorithm/test/resource_test/config.json";
    Network network(path);
    Network_Optimizer optimizer(network, Sphere_Coordinate(0, 0), 0.5, DayTime(hours(1), minutes(0)), Day(Monday, SCHOOL_DAYS));
    std::vector<Algorithm_Station> result = optimizer.Optimize();

    DayTime res = DayTime(hours(1), minutes(3)) + seconds((int)std::round(network.Get_Station()[3].Get_Distance_To(network.Get_Station()[4])));

    SCOPED_TRACE("Station A :" + Algorithm_Station::Get_Station_By_Name(result, "Station A").Get_Reach_Time().ToString() + " Expect " + DayTime(hours(1), minutes(0)).ToString() + "\n");
    SCOPED_TRACE("Station B :" + Algorithm_Station::Get_Station_By_Name(result, "Station B").Get_Reach_Time().ToString() + " Expect " + DayTime(hours(1), minutes(11)).ToString() + "\n");
    SCOPED_TRACE("Station C :" + Algorithm_Station::Get_Station_By_Name(result, "Station C").Get_Reach_Time().ToString() + " Expect " + DayTime(hours(1), minutes(16)).ToString() + "\n");
    SCOPED_TRACE("Station D :" + Algorithm_Station::Get_Station_By_Name(result, "Station D").Get_Reach_Time().ToString() + " Expect " + DayTime(hours(1), minutes(3)).ToString() + "\n");
    SCOPED_TRACE("Station E :" + Algorithm_Station::Get_Station_By_Name(result, "Station E").Get_Reach_Time().ToString() + " Expect " + res.ToString() + "\n");
    SCOPED_TRACE("Station F ;" + Algorithm_Station::Get_Station_By_Name(result, "Station F").Get_Reach_Time().ToString() + " Expect " + DayTime(hours(1), minutes(3)).ToString() + "\n");

    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station A").Get_Reach_Time(), DayTime(hours(1), minutes(0)));
    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station B").Get_Reach_Time(), DayTime(hours(1), minutes(11)));
    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station C").Get_Reach_Time(), DayTime(hours(1), minutes(16)));
    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station D").Get_Reach_Time(), DayTime(hours(1), minutes(3)));

    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station E").Get_Reach_Time(), res);
    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station F").Get_Reach_Time(), DayTime(hours(1), minutes(3)));
   
}



TEST_F(Network_Optimizer_Test, Get_Closest_Time_To_Station)
{
    std::filesystem::path path = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/algorithm/test/resource_test/config.json";
    Network network(path);
    DayTime start_time = DayTime(hours(20), minutes(0));
    Sphere_Coordinate start_coordinate(0, 0);
    Network_Optimizer optimizer(network, start_coordinate, 1, start_time, Day(Monday, SCHOOL_DAYS));
    std::vector<Algorithm_Station> result = optimizer.Optimize();

    DayTime res1 = start_time + seconds((int)std::round(network.Get_Station()[1].Get_Distance_To(start_coordinate)));
    DayTime res2 = start_time + seconds((int)std::round(network.Get_Station()[2].Get_Distance_To(start_coordinate)));
    DayTime res3 = start_time + seconds((int)std::round(network.Get_Station()[3].Get_Distance_To(start_coordinate)));
    DayTime res4 = start_time + seconds((int)std::round(network.Get_Station()[4].Get_Distance_To(start_coordinate)));
    DayTime res5 = start_time + seconds((int)std::round(network.Get_Station()[5].Get_Distance_To(start_coordinate)));

    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station A").Get_Reach_Time(), start_time);
    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station B").Get_Reach_Time(), res1);
    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station C").Get_Reach_Time(), res2);
    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station D").Get_Reach_Time(), res3);
    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station E").Get_Reach_Time(), res4);
    ASSERT_EQ(Algorithm_Station::Get_Station_By_Name(result, "Station F").Get_Reach_Time(), res5);
   
}
