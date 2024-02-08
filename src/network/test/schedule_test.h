#ifndef SCHEDULE_TEST_H
#define SCHEDULE_TEST_H

#include <gtest/gtest.h>
#include <memory>

#include "includes/network/station.h"
#include "includes/network/schedule.h"


class Schedule_Test : public ::testing::Test {
public:
	static void SetUpTestSuite();

	static std::unique_ptr<Network::Schedule> s_schedule;
	static std::vector<Network::Station> s_stations;
	static Network::TimeTable s_timetable;
};


#endif //SCHEDULE_TEST_H