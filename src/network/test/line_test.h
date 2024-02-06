#ifndef LINE_TEST_H
#define LINE_TEST_H

#include <gtest/gtest.h>

#include "includes/network/station.h"

struct LINE_TESTING_STRUCTUR
{
	std::string name;
	std::vector<Network::Station> stations;
	std::vector<Network::Station> not_contained;

	LINE_TESTING_STRUCTUR(std::string&& name, std::vector<Network::Station>&& stations, std::vector<Network::Station>&& not_contained):
		name(std::move(name)),
		stations(std::move(stations)),
		not_contained(std::move(not_contained))
	{
	}
	LINE_TESTING_STRUCTUR(const LINE_TESTING_STRUCTUR&) = delete;
};

class Line_Test : public ::testing::Test, public ::testing::WithParamInterface<LINE_TESTING_STRUCTUR> {

};


#endif //LINE_TEST_H