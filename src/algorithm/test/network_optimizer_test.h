
#ifndef NETWORK_OPTIMIZER_TEST_H
#define NETWORK_OPTIMIZER_TEST_H

#include <gtest/gtest.h>

#include "includes/context/scheduled_network.h"

class Network_Optimizer_Test : public ::testing::Test {
	static void SetUpTestSuite();

public:
	static Context::Scheduled_Network s_context;
};


#endif //NETWORK_OPTIMIZER_TEST_H