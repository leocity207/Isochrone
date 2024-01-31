#ifndef GENERAL_TEST_H
#define GENERAL_TEST_H

#include <gtest/gtest.h>
#include <string>
#include <utility>


class General_Test : public ::testing::Test {
	
};


class Space_Triming_Test : public General_Test, public ::testing::WithParamInterface<std::pair<std::string,std::string>> {

};


class Angle_Parsing : public General_Test, public ::testing::WithParamInterface<std::tuple<std::string,bool,double>> {

};


#endif //GENERAL_TEST_H