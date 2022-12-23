#include "daytime_test.h"
#include "includes/utils/daytime.h"

#include "includes/utils/exception_def.h"

#include <string_view>


TEST(DayTime_Test, normal_constructor)
{
	DayTime test = DayTime(std::chrono::hours(10), std::chrono::minutes(12));
	ASSERT_EQ(test.GetTime(), std::chrono::minutes(10 * 60 + 12));
}



TEST_P(DayTime_Test_String_Parser, parsing_constructor)
{
    auto [angle_str, valid, value] = GetParam();

    if (valid == OK)
    {
        
        EXPECT_NO_THROW(
            DayTime returned = DayTime::From_Time_String(angle_str).value();
            ASSERT_EQ(returned.GetTime(), std::chrono::minutes(value));
        );
        
    }
    else if (valid == THROW)
    {
        EXPECT_THROW(DayTime::From_Time_String(angle_str), Time_Badly_Formatted);
    }
    else
    {
        EXPECT_NO_THROW(
            std::optional<DayTime> returned = DayTime::From_Time_String(angle_str);
        
            ASSERT_FALSE(returned.has_value());
        );
    }
}

std::string DayTime_Test_String_Parser_Naming(testing::TestParamInfo<std::tuple<std::string, DAYTIME_RETURN_TYPE, int>> id)
{
    switch (id.index)
    {
    case 0:
        return "valid_hour";
    case 1:
        return "sapce_hour";
    case 2:
        return "wrong_string_with_point";
    case 3:
        return "wrong_string_without_point";
    case 4:
        return "void_string";
    }
}

INSTANTIATE_TEST_SUITE_P(
    test_string,
    DayTime_Test_String_Parser,
    ::testing::Values(
        std::make_tuple("10:01"  , OK     , 10*60+1),
        std::make_tuple(" 9:3 "  , THROW  , 0),
        std::make_tuple(":"      , THROW  , 0),
        std::make_tuple("dksfjsl", THROW  , 0),
        std::make_tuple(""       , NULLOPT, 0)),
    DayTime_Test_String_Parser_Naming);