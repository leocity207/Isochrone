#include "line_test.h"

// STL
#include <ranges>

// Network
#include "includes/network/line.h"

std::map<std::string, Network::Station> SetupStationList()
{
	std::map<std::string, Network::Station> tmp;
	tmp.emplace("A", Network::Station(Coordinate::Spherical(0, 0), "Station A"));
	tmp.emplace("B", Network::Station(Coordinate::Spherical(0, 0), "Station B"));
	tmp.emplace("C", Network::Station(Coordinate::Spherical(0, 0), "Station C"));
	tmp.emplace("D", Network::Station(Coordinate::Spherical(0, 0), "Station D"));
	tmp.emplace("false A", Network::Station(Coordinate::Spherical(0, 0), "Station false A"));
	tmp.emplace("F", Network::Station(Coordinate::Spherical(0, 0), "Station F"));
	return tmp;
}

std::map<std::string,Network::Station> Line_Test::s_stations_list = SetupStationList();

//////////////////////////////////////
///
Network::Line MakeLine(const LINE_TESTING_STRUCTUR& structure)
{
	std::vector<Network::Station_CRef> station_ref;
	return Network::Line(std::vector<Network::Station_CRef>(structure.stations), std::string(structure.name));
}

TEST_P(Line_Test, Get_Station_List)
{
	const LINE_TESTING_STRUCTUR& param_struct = GetParam();
	Network::Line line = MakeLine(param_struct);
	EXPECT_EQ(line.Get_Station_List().size(), param_struct.stations.size());
	for (int i : std::views::iota(0ul, param_struct.stations.size()))
		EXPECT_EQ(line.Get_Station_List()[i].get(), param_struct.stations[i].get());
}

TEST_P(Line_Test, Order)
{
	const LINE_TESTING_STRUCTUR& param_struct = GetParam();
	if (param_struct.name == "reapeating  line")
		GTEST_SKIP() << "Reapeating station in a line is not supported";
	Network::Line line = MakeLine(param_struct);
	if(param_struct.stations.size())
		for (size_t i : std::views::iota(0ul, param_struct.stations.size()-1))
			for (size_t j : std::views::iota(i + 1ul, param_struct.stations.size()))
			{
				EXPECT_EQ(line.Order(line.Get_Station_List()[i], line.Get_Station_List()[j]), std::strong_ordering::less);
				EXPECT_EQ(line.Order(line.Get_Station_List()[j], line.Get_Station_List()[i]), std::strong_ordering::greater);
			}
	for (size_t i : std::views::iota(0ul, param_struct.stations.size()))
		EXPECT_EQ(line.Order(line.Get_Station_List()[i].get(), line.Get_Station_List()[i].get()), std::strong_ordering::equivalent);

	if (param_struct.stations.size())
		for (const Network::Station& station : param_struct.not_contained)
			EXPECT_THROW({ line.Order(line.Get_Station_List()[0], station); }, STATION_NOT_IN_SCHEDULE);

	if (param_struct.stations.size())
		for (const Network::Station& station : param_struct.not_contained)
			EXPECT_THROW({ line.Order(station, line.Get_Station_List()[0]); }, STATION_NOT_IN_SCHEDULE);
	for (const Network::Station& station : param_struct.not_contained)
		EXPECT_THROW({ line.Order(station, station); }, STATION_NOT_IN_SCHEDULE);
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

TEST_P(Line_Test, Get_Station_Index)
{
	const LINE_TESTING_STRUCTUR& param_struct = GetParam();
	if (param_struct.name == "reapeating  line")
		GTEST_SKIP() << "Reapeating station in a line is not supported";
	Network::Line line = MakeLine(param_struct);
	for (size_t i : std::views::iota(0ul, param_struct.stations.size()))
		EXPECT_EQ(line.Get_Station_Index(param_struct.stations[i]).value(), i);
	for (const Network::Station& station : param_struct.not_contained)
		EXPECT_FALSE(line.Get_Station_Index(station).has_value());
}

///////////////////////////////////////////////////
/// a simple line composed of four station A,B,C,D
LINE_TESTING_STRUCTUR Make_Simple_Exemple()
{
	std::vector<Network::Station_CRef> stations;
	stations.emplace_back(Line_Test::s_stations_list.at("A"));
	stations.emplace_back(Line_Test::s_stations_list.at("B"));
	stations.emplace_back(Line_Test::s_stations_list.at("C"));
	stations.emplace_back(Line_Test::s_stations_list.at("D"));
	std::vector<Network::Station_CRef> not_contained;
	not_contained.emplace_back(Line_Test::s_stations_list.at("false A"));
	not_contained.emplace_back(Line_Test::s_stations_list.at("F"));
	std::string name("The liné is");
	return LINE_TESTING_STRUCTUR(std::move(name), std::move(stations), std::move(not_contained));
}

/////////////////////////////////////////
/// A line with no station
LINE_TESTING_STRUCTUR Make_Null_Exemple()
{
	std::vector<Network::Station_CRef> stations;
	std::vector<Network::Station_CRef> not_contained;
	not_contained.emplace_back(Line_Test::s_stations_list.at("false A"));
	not_contained.emplace_back(Line_Test::s_stations_list.at("F"));

	std::string name("null line");
	return LINE_TESTING_STRUCTUR(std::move(name), std::move(stations), std::move(not_contained));
}


/////////////////////////////////////////////////////////////////////////////////
/// A line where one station Repeat itself (A,B,C,A)
/// currently reapeating station are not supported for ordering  or getting index
LINE_TESTING_STRUCTUR Make_Reapeating_Station_Exemple()
{
	std::vector<Network::Station_CRef> stations;
	stations.emplace_back(Line_Test::s_stations_list.at("A"));
	stations.emplace_back(Line_Test::s_stations_list.at("B"));
	stations.emplace_back(Line_Test::s_stations_list.at("C"));
	stations.emplace_back(Line_Test::s_stations_list.at("A"));
	std::vector<Network::Station_CRef> not_contained;
	not_contained.emplace_back(Line_Test::s_stations_list.at("false A"));
	not_contained.emplace_back(Line_Test::s_stations_list.at("F"));
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


