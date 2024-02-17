#ifndef DAY_INFO_TEST_H
#define DAY_INFO_TEST_H

#include <gtest/gtest.h>

// Network
#include "includes/network/day_info.h"

class Day_Test : public ::testing::Test,public ::testing::WithParamInterface < std::tuple<std::chrono::weekday,Network::DAY_TYPE> > {
    
};

class Day_Template_Test : public ::testing::Test, public ::testing::WithParamInterface < std::tuple<bool, bool, bool, bool, bool, bool, bool, bool, bool, bool> > {

};


#endif //DAY_INFO_TEST_H