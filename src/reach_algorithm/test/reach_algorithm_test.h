
#ifndef NETWORK_OPTIMIZER_TEST_H
#define NETWORK_OPTIMIZER_TEST_H

#include <gtest/gtest.h>

#include "includes/context/scheduled_network.h"

class Reach_Algorithm_Test : public ::testing::Test {

public:
	static void SetUpTestSuite();
	static std::unique_ptr<Context::Scheduled_Network> s_context;
};


#endif //NETWORK_OPTIMIZER_TEST_H