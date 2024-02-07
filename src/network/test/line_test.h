#ifndef LINE_TEST_H
#define LINE_TEST_H

#include <gtest/gtest.h>

#include "includes/network/station.h"

struct LINE_TESTING_STRUCTUR
{
	std::string name;
	std::vector<Network::Station_CRef> stations;
	std::vector<Network::Station_CRef> not_contained;

	LINE_TESTING_STRUCTUR(std::string&& name, std::vector<Network::Station_CRef>&& stations, std::vector<Network::Station_CRef>&& not_contained):
		name(std::move(name)),
		stations(std::move(stations)),
		not_contained(std::move(not_contained))
	{
	}
};

class Line_Test : public ::testing::Test, public ::testing::WithParamInterface<LINE_TESTING_STRUCTUR> {

public:
	static std::map<std::string, Network::Station > s_stations_list;
	static bool s_setup;

};


#endif //LINE_TEST_H