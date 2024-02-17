#ifndef SCHEDULED_LINE_TEST_H
#define SCHEDULED_LINE_TEST_H

#include <gtest/gtest.h>

// Network
#include "includes/network/station.h"
#include "includes/network/schedule.h"
#include "includes/network/scheduled_line.h"


class Scheduled_Line_Test : public ::testing::Test {
public:
	static void SetUpTestSuite();

	static std::unique_ptr<Network::Scheduled_Line> s_schedule;
	static std::vector<Network::Station> s_stations;
	static Network::TimeTable s_timetable;
	static Network::TimeTable s_timetable2;
    
};


#endif //SCHEDULED_LINE_TEST_H