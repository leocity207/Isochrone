#include "line_test.h"

#include "includes/network/line.h"

#include <functional>
#include <ranges>

Network::Line MakeLine(const LINE_TESTING_STRUCTUR& structure)
{
	std::vector<Network::Station_CRef> station_ref;
	return Network::Line(std::vector<Network::Station_CRef>(structure.stations.begin(), structure.stations.end()), std::string(structure.name));
}

TEST_P(Line_Test, Get_Station_List)
{
	const LINE_TESTING_STRUCTUR& param_struct = GetParam();
	Network::Line line = MakeLine(param_struct);
	EXPECT_EQ(line.Get_Station_List().size(), param_struct.stations.size());
	for (int i : std::views::iota(0ul, param_struct.stations.size()))
		EXPECT_EQ(line.Get_Station_List()[i], param_struct.stations[i]);
}

TEST_P(Line_Test, Order)
{
	const LINE_TESTING_STRUCTUR& param_struct = GetParam();
	Network::Line line = MakeLine(param_struct);
	for (size_t i : std::views::iota(0ul, param_struct.stations.size()-1))
		for (size_t j : std::views::iota(i + 1ul, param_struct.stations.size()))
		{
			EXPECT_TRUE(line.Order(line.Get_Station_List()[i], line.Get_Station_List()[j]));
			EXPECT_FALSE(line.Order(line.Get_Station_List()[j], line.Get_Station_List()[i]));
		}
	for (size_t i : std::views::iota(0ul, param_struct.stations.size()))
		EXPECT_THROW({ line.Order(line.Get_Station_List()[i].get(), line.Get_Station_List()[i].get());}, CANNOT_ORDER_SAME_STATION);

	for (const Network::Station& station : param_struct.not_contained)
		EXPECT_THROW({ line.Order(line.Get_Station_List()[0], station); }, STATION_NOT_IN_SCHEDULE);

	for (const Network::Station& station : param_struct.not_contained)
		EXPECT_THROW({ line.Order(station, line.Get_Station_List()[0]); }, STATION_NOT_IN_SCHEDULE);
}

TEST_P(Line_Test, Contain)
{
	const LINE_TESTING_STRUCTUR& param_struct = GetParam();
	Network::Line line = MakeLine(param_struct);
	for (const Network::Station& station : param_struct.stations)
		EXPECT_TRUE(line.Contain(station));
	for (const Network::Station& station : param_struct.not_contained)
		EXPECT_FALSE(line.Contain(station));
}

TEST_F(Line_Test, Get_Station_Index)
{
	const LINE_TESTING_STRUCTUR& param_struct = GetParam();
	Network::Line line = MakeLine(param_struct);
	for (size_t i : std::views::iota(0ul, param_struct.stations.size()))
		EXPECT_EQ(line.Get_Station_Index(param_struct.stations[i]).value(), i);
	for (const Network::Station& station : param_struct.not_contained)
		EXPECT_FALSE(line.Get_Station_Index(station).has_value());
}

LINE_TESTING_STRUCTUR Make_Simple_Exemple()
{
	Network::Station A(Sphere_Coordinate(0, 0), "Station A");
	Network::Station B(Sphere_Coordinate(0, 0), "Station B");
	Network::Station C(Sphere_Coordinate(0, 0), "Station C");
	Network::Station D(Sphere_Coordinate(0, 0), "Station D");

	Network::Station false_A(Sphere_Coordinate(0, 0), "Station A");
	Network::Station F(Sphere_Coordinate(0, 0), "Station F");

	std::vector<Network::Station> stations;
	stations.emplace_back(std::move(A));
	stations.emplace_back(std::move(B));
	stations.emplace_back(std::move(C));
	stations.emplace_back(std::move(D));
	std::vector<Network::Station> not_contained;
	not_contained.emplace_back(std::move(false_A));
	not_contained.emplace_back(std::move(F));
	std::string name("The liné is");
	return LINE_TESTING_STRUCTUR(std::move(name), std::move(stations), std::move(not_contained));
}

LINE_TESTING_STRUCTUR Make_Null_Exemple()
{
	Network::Station false_A(Sphere_Coordinate(0, 0), "Station A");
	Network::Station F(Sphere_Coordinate(0, 0), "Station F");

	std::vector<Network::Station> stations = {};
	std::vector<Network::Station> not_contained;
	not_contained.emplace_back(std::move(false_A));
	not_contained.emplace_back(std::move(F));

	std::string name("null line");
	return LINE_TESTING_STRUCTUR(std::move(name), std::move(stations), std::move(not_contained));
}

LINE_TESTING_STRUCTUR Make_Reapeating_Station_Exemple()
{
	Network::Station A(Sphere_Coordinate(0, 0), "Station A");
	Network::Station B(Sphere_Coordinate(0, 0), "Station B");
	Network::Station C(Sphere_Coordinate(0, 0), "Station C");
	Network::Station D(Sphere_Coordinate(0, 0), "Station D");


	Network::Station false_A(Sphere_Coordinate(0, 0), "Station A");
	Network::Station F(Sphere_Coordinate(0, 0), "Station F");

	std::vector<Network::Station> stations;
	stations.emplace_back(std::move(A));
	stations.emplace_back(std::move(B));
	stations.emplace_back(std::move(C));
	stations.emplace_back(std::move(A));
	std::vector<Network::Station> not_contained;
	not_contained.emplace_back(std::move(false_A));
	not_contained.emplace_back(std::move(F));

	std::string name("reapeating  line");

	return LINE_TESTING_STRUCTUR(std::move(name), std::move(stations), std::move(not_contained));
}

std::string Space_Triming_Test_Naming(testing::TestParamInfo<LINE_TESTING_STRUCTUR> id)
{
	switch (id.index)
	{
	case 0:
		return "Simple";
	case 1:
		return "Null";
	case 2:
		return "Reapeating";
	default:
		throw "Unexpected index";
	}
}

INSTANTIATE_TEST_SUITE_P(
	test_string,
	Line_Test,
	::testing::Values(
		Make_Simple_Exemple(),
		Make_Null_Exemple(),
		Make_Reapeating_Station_Exemple()),
	Space_Triming_Test_Naming
);