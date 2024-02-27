#include "csv_validator_test.h"

#include "includes/utils/daytime.h"
#include "includes/resource/csv/validator/timetable.h"

using namespace std::chrono;


/////////////////////////////////////////////////////////////
/// Noraml test where the Timetable is exepected to be valide
TEST_F(CSV_Validator_Test, normal)
{
	DayTime a00 = DayTime::From_Time_String("6:00").value() ;  DayTime a10 = DayTime::From_Time_String("6:10").value();
	DayTime a01 = DayTime::From_Time_String("7:00").value() ;  DayTime a11 = DayTime::From_Time_String("9:20").value(); DayTime a21 = DayTime::From_Time_String("8:00").value();
	DayTime a02 = DayTime::From_Time_String("9:20").value() ;                                                           DayTime a22 = DayTime::From_Time_String("9:20").value();
	DayTime a03 = DayTime::From_Time_String("10:10").value(); DayTime a13 = DayTime::From_Time_String("10:20").value(); DayTime a23 = DayTime::From_Time_String("10:30").value();
	DayTime a04 = DayTime::From_Time_String("12:00").value(); DayTime a14 = DayTime::From_Time_String("12:10").value();

	TimeTable timetable = { {a00,a10,std::nullopt},{a01,a11,a21 },{a02,std::nullopt,a22},{a03,a13,a23},{a04,a14,std::nullopt} };

	const auto errors = CSV::Parser::Validator::Validate(timetable,"valide");
	EXPECT_EQ(errors.size(), 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// When time is the same two consecutive time it is exepected to be valide situation (two stop in the same minute)
TEST_F(CSV_Validator_Test, normal_following)
{
	DayTime a00 = DayTime::From_Time_String("6:00").value() ; DayTime a10 = DayTime::From_Time_String("6:10").value() ;
	DayTime a01 = DayTime::From_Time_String("7:00").value() ; DayTime a11 = DayTime::From_Time_String("9:20").value() ; DayTime a21 = DayTime::From_Time_String("8:00").value();
	DayTime a02 = DayTime::From_Time_String("9:20").value() ;                                                           DayTime a22 = DayTime::From_Time_String("9:20").value();
	DayTime a03 = DayTime::From_Time_String("10:10").value(); DayTime a13 = DayTime::From_Time_String("9:20").value() ; DayTime a23 = DayTime::From_Time_String("10:30").value();
	DayTime a04 = DayTime::From_Time_String("10:10").value(); DayTime a14 = DayTime::From_Time_String("12:10").value();

	TimeTable timetable = { {a00,a10,std::nullopt},{a01,a11,a21 },{a02,std::nullopt,a22},{a03,a13,a23},{a04,a14,std::nullopt} };

	const auto errors = CSV::Parser::Validator::Validate(timetable, "valide");
	EXPECT_EQ(errors.size(), 0);
}

////////////////////////////////////////
/// Test where there is two wrong values
TEST_F(CSV_Validator_Test, strange_time)
{
	DayTime a00 = DayTime::From_Time_String("6:00").value() ; DayTime a10 = DayTime::From_Time_String("6:10").value() ;
	DayTime a01 = DayTime::From_Time_String("7:00").value() ; DayTime a11 = DayTime::From_Time_String("9:20").value() ; DayTime a21 = DayTime::From_Time_String("8:00").value();
	DayTime a02 = DayTime::From_Time_String("9:20").value() ;                                                           DayTime a22 = DayTime::From_Time_String("7:20").value();
	DayTime a03 = DayTime::From_Time_String("10:10").value(); DayTime a13 = DayTime::From_Time_String("10:20").value(); DayTime a23 = DayTime::From_Time_String("6:30").value();
	DayTime a04 = DayTime::From_Time_String("12:00").value(); DayTime a14 = DayTime::From_Time_String("12:10").value();

	TimeTable timetable = { {a00,a10,std::nullopt},{a01,a11,a21 },{a02,std::nullopt,a22},{a03,a13,a23},{a04,a14,std::nullopt} };
	const auto errors = CSV::Parser::Validator::Validate(timetable, "valide");
	EXPECT_EQ(errors.size(), 2);

	EXPECT_NE(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time*>(errors[0].get()), nullptr);
	EXPECT_NE(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time*>(errors[1].get()), nullptr);

	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time&>(*errors[0]).Get_i(), 2);
	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time&>(*errors[0]).Get_j(), 2);
	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time&>(*errors[0]).Get_Time(), DayTime(7h, 20min));

	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time&>(*errors[1]).Get_i(), 3);
	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time&>(*errors[1]).Get_j(), 2);
	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time&>(*errors[1]).Get_Time(), DayTime(6h, 30min));
}

/////////////////////////////////////////////////
/// Test when the wrong value is after a nullopt
TEST_F(CSV_Validator_Test, strange_time_with_nullopt)
{
	DayTime a00 = DayTime::From_Time_String("6:00").value() ; DayTime a10 = DayTime::From_Time_String("6:10").value() ;
	DayTime a01 = DayTime::From_Time_String("7:00").value() ; DayTime a11 = DayTime::From_Time_String("9:20").value() ;  DayTime a21 = DayTime::From_Time_String("8:00").value();
	DayTime a02 = DayTime::From_Time_String("9:20").value() ;                                                           DayTime a22 = DayTime::From_Time_String("9:20").value();
	DayTime a03 = DayTime::From_Time_String("10:10").value(); DayTime a13 = DayTime::From_Time_String("6:20").value() ; DayTime a23 = DayTime::From_Time_String("10:30").value();
	DayTime a04 = DayTime::From_Time_String("12:00").value(); DayTime a14 = DayTime::From_Time_String("12:10").value();

	TimeTable timetable = { {a00,a10,std::nullopt},{a01,a11,a21 },{a02,std::nullopt,a22},{a03,a13,a23},{a04,a14,std::nullopt} };
	const auto errors = CSV::Parser::Validator::Validate(timetable, "valide");
	EXPECT_EQ(errors.size(), 1);

	EXPECT_NE(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time*>(errors[0].get()), nullptr);

	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time&>(*errors[0]).Get_i(), 3);
	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time&>(*errors[0]).Get_j(), 1);

	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Time&>(*errors[0]).Get_Time(), DayTime(6h,20min));
}

///////////////////////////////////////////////
/// Test when one line is longer than the other
TEST_F(CSV_Validator_Test, strange_line_size)
{
	DayTime a00 = DayTime::From_Time_String("6:00").value() ;  DayTime a10 = DayTime::From_Time_String("6:10").value();
	DayTime a01 = DayTime::From_Time_String("7:00").value() ;  DayTime a11 = DayTime::From_Time_String("9:20").value(); DayTime a21 = DayTime::From_Time_String("8:00").value();
	DayTime a02 = DayTime::From_Time_String("9:20").value() ;                                                           DayTime a22 = DayTime::From_Time_String("9:20").value();
	DayTime a03 = DayTime::From_Time_String("10:10").value(); DayTime a13 = DayTime::From_Time_String("10:20").value(); DayTime a23 = DayTime::From_Time_String("10:30").value();
	DayTime a04 = DayTime::From_Time_String("2:00").value() ; DayTime a14 = DayTime::From_Time_String("12:10").value();

	TimeTable timetable = { {a00,a10,std::nullopt},{a01,a11,a21 },{a02,std::nullopt,a22,std::nullopt},{a03,a13,a23},{a04,a14,std::nullopt} };
	const auto errors = CSV::Parser::Validator::Validate(timetable, "valide");
	EXPECT_EQ(errors.size(), 1);
	EXPECT_NE(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Size*>(errors[0].get()) , nullptr);

	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Size&>(*errors[0]).Get_i(), 2);
	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Size&>(*errors[0]).Get_Anormal_Size(), 4);
	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Size&>(*errors[0]).Get_Normal_Size(), 3);
}

//////////////////////////
/// The first ligne is null
TEST_F(CSV_Validator_Test, strange_time_first_line_null)
{
	DayTime a00 = DayTime::From_Time_String("6:00").value() ;  DayTime a10 = DayTime::From_Time_String("6:10").value() ;
	DayTime a01 = DayTime::From_Time_String("7:00").value() ;  DayTime a11 = DayTime::From_Time_String("9:20").value() ;  DayTime a21 = DayTime::From_Time_String("8:00").value();
	DayTime a02 = DayTime::From_Time_String("9:20").value() ;                                                            DayTime a22 = DayTime::From_Time_String("9:20").value();
	DayTime a03 = DayTime::From_Time_String("10:10").value(); DayTime a13 = DayTime::From_Time_String("9:40").value() ; DayTime a23 = DayTime::From_Time_String("10:30").value();
	DayTime a04 = DayTime::From_Time_String("12:00").value(); DayTime a14 = DayTime::From_Time_String("12:10").value();
	TimeTable timetable = { {},{a01,a11,a21 },{a02,std::nullopt,a22,std::nullopt},{a03,a13,a23},{a04,a14,std::nullopt}};
	const auto errors = CSV::Parser::Validator::Validate(timetable, "valide");
	EXPECT_EQ(errors.size(), 4);
	EXPECT_NE(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Size*>(errors[0].get()), nullptr);

	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Size&>(*errors[0]).Get_i(), 1);
	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Size&>(*errors[0]).Get_Anormal_Size(), 3);
	EXPECT_EQ(dynamic_cast<CSV::Parser::Validator::TimeTable_Error_Size&>(*errors[0]).Get_Normal_Size(), 0);
}

///////////////////////////////
/// The whole timetable is null
TEST_F(CSV_Validator_Test, strange_time_null)
{
	TimeTable timetable;
	const auto errors = CSV::Parser::Validator::Validate(timetable, "valide");
	EXPECT_EQ(errors.size(), 1);
}