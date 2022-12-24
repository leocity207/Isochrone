#ifndef SCHEDULE_TEST_H
#define SCHEDULE_TEST_H

#include <gtest/gtest.h>
#include <memory>

#include "includes/network_optimizer/station.h"
class Schedule;

class Schedule_Test : public ::testing::Test {
public:
    static void SetUpTestSuite();


    static std::unique_ptr<Schedule> s_schedule;
    static std::vector<Station> s_stations;
};


#endif //SCHEDULE_TEST_H