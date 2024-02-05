#ifndef ALGORITHM_STATION_TEST_H
#define ALGORITHM_STATION_TEST_H

#include <gtest/gtest.h>

#include "includes/context/scheduled_network.h"

class Algorithm_Station_Test : public ::testing::Test {

public:
	static void SetUpTestSuite();
	static std::unique_ptr<Context::Scheduled_Network> s_context;
};


#endif //ALGORITHM_STATION_TEST_H