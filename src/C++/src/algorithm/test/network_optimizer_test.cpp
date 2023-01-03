#include "network_optimizer_test.h"

#include "includes/algorithm/network_optimizer.h"

using namespace std::chrono;

TEST_F(Network_Optimizer_Test, test_with_normal_day)
{
    std::filesystem::path path = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/algorithm/test/resource_test/config.json";
    Network network(path);
    Network_Optimizer optimizer(network,Sphere_Coordinate(0,0),1,DayTime(hours(0),minutes(0)),Day(Monday,SCHOOL_DAYS));
    std::vector<Algorithm_Station> result = optimizer.Optimize();

    ASSERT_EQ(result[0].Get_Reach_Time(), DayTime(hours(0),minutes(0)));
    ASSERT_EQ(result[1].Get_Reach_Time(), DayTime(hours(0),minutes(3)));
    ASSERT_EQ(result[2].Get_Reach_Time(), DayTime(hours(0),minutes(3)));
    ASSERT_EQ(result[3].Get_Reach_Time(), DayTime(hours(0),minutes(3)));
    ASSERT_EQ(result[4].Get_Reach_Time(), DayTime(hours(0),minutes(4)));
    ASSERT_EQ(result[5].Get_Reach_Time(), DayTime(hours(0),minutes(3)));
}

TEST_F(Network_Optimizer_Test, bypass)
{
    std::filesystem::path path = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/algorithm/test/resource_test/config.json";
    Network network(path);
    Network_Optimizer optimizer(network,Sphere_Coordinate(0,0),1,DayTime(hours(1),minutes(0)),Day(Monday,SCHOOL_DAYS));
    std::vector<Algorithm_Station> result = optimizer.Optimize();

    ASSERT_EQ(result[0].Get_Reach_Time(), DayTime(hours(1),minutes(0)));
    ASSERT_EQ(result[1].Get_Reach_Time(), DayTime(hours(1),minutes(35)));
    ASSERT_EQ(result[2].Get_Reach_Time(), DayTime(hours(1),minutes(36)));
    ASSERT_EQ(result[3].Get_Reach_Time(), DayTime(hours(1),minutes(3)));
    DayTime res = DayTime(hours(1),minutes(3))+seconds((int)std::round(network.Get_Station()[3].Get_Distance_To(network.Get_Station()[4])));
    ASSERT_EQ(result[4].Get_Reach_Time(), res);
    ASSERT_EQ(result[5].Get_Reach_Time(), DayTime(hours(1),minutes(3)));
}



TEST_F(Network_Optimizer_Test, Get_Closest_Time_To_Station)
{
    std::filesystem::path path = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/algorithm/test/resource_test/config.json";
    Network network(path);
    DayTime start_time = DayTime(hours(20),minutes(0));
    Network_Optimizer optimizer(network,Sphere_Coordinate(0,0),1,DayTime(hours(1),minutes(0)),Day(Monday,SCHOOL_DAYS));
    std::vector<Algorithm_Station> result = optimizer.Optimize();

    DayTime res1 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[1])));
    DayTime res2 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[2])));
    DayTime res3 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[3])));
    DayTime res4 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[4])));
    DayTime res5 = start_time+seconds((int)std::round(network.Get_Station()[0].Get_Distance_To(network.Get_Station()[5])));

    ASSERT_EQ(result[0].Get_Reach_Time(), start_time);
    ASSERT_EQ(result[1].Get_Reach_Time(), res1);
    ASSERT_EQ(result[2].Get_Reach_Time(), res2);
    ASSERT_EQ(result[3].Get_Reach_Time(), res3);
    ASSERT_EQ(result[4].Get_Reach_Time(), res4);
    ASSERT_EQ(result[5].Get_Reach_Time(), res5);
}