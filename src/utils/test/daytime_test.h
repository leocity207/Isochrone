#ifndef DAYTIME_TEST_H
#define DAYTIME_TEST_H

#include <gtest/gtest.h>

// STD
#include <string>

enum DAYTIME_RETURN_TYPE
{
	OK,
	THROW,
	NULLOPT
};


class DayTime_Test : public ::testing::Test {
	
};

class DayTime_Test_String_Parser : public DayTime_Test, public ::testing::WithParamInterface<std::tuple<std::string, DAYTIME_RETURN_TYPE, int>> {

};


#endif //DAYTIME_TEST_H