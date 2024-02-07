#ifndef DAY_INFO_TEST_H
#define DAY_INFO_TEST_H

#include <gtest/gtest.h>

class Day_Test : public ::testing::Test, ::testing::WithParamInterface < std::tuple<std::chrono::weekday,Network::DAY_TYPE> > {
    
};


class Day_template_Test : public ::testing::Test {

};


#endif //DAY_INFO_TEST_H