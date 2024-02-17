#include "general_test.h"


// STL
#include <string_view>

// Utils
#include "includes/utils/general.h"
#include "includes/utils/exception_def.h"


TEST_P(Space_Triming_Test, string_view) {
	std::string_view test_view = GetParam().first;
	std::string_view returned;
	EXPECT_NO_THROW(returned = Generals::Trim_Space_Front_Back(test_view));
	ASSERT_EQ(returned, GetParam().second);
}

TEST_P(Space_Triming_Test, string) {
	std::string test_string = std::string(GetParam().first);
	std::string_view returned;
	EXPECT_NO_THROW(returned = Generals::Trim_Space_Front_Back(std::move(test_string)));
	ASSERT_EQ(returned, GetParam().second);
}

std::string Space_Triming_Test_Naming(testing::TestParamInfo<std::pair<std::string,std::string>> id)
{
	switch (id.index)
	{
	case 0:
		return "Void_string";
	case 1:
		return "front_and_back";
	case 2:
		return "front";
	case 3:
		return "back";
	case 4:
		return "No_space";
	case 5:
		return "only_space";
	case 6:
		return "leading_utf8_charachter";
	default:
		throw "Unexpected index";
	}
}

INSTANTIATE_TEST_SUITE_P(
	test_string,
	Space_Triming_Test,
	::testing::Values(
		std::make_pair("",""),
		std::make_pair("  123:212  ","123:212"),
		std::make_pair("             45", "45"),
		std::make_pair("45    ","45"),
		std::make_pair("ajkl�*$", "ajkl�*$"),
		std::make_pair("        ",""),
		std::make_pair("Étienne Rey                 ", "Étienne Rey")),
	Space_Triming_Test_Naming);




/////////////////////////////////////////////////////////////////////////////////////////////////

TEST_P(Angle_Parsing, _)
{
	auto [angle_str,valid,value] = GetParam();

	if (valid)
	{
		EXPECT_NO_THROW(
			{
				double returned;
				returned = Generals::Parse_Angle(angle_str);
				EXPECT_DOUBLE_EQ(returned, value);
			});
	}
	else
	{
		EXPECT_THROW(Generals::Parse_Angle(angle_str), ANGLE_BADLY_FORMATED);
	}
}

std::string Angle_parsing_Test_Naming(testing::TestParamInfo<std::tuple<std::string,bool,double>> id)
{
	switch (id.index)
	{
	case 0:
		return "Valid_int";
	case 1:
		return "valid_double";
	case 2:
		return "wrong_string";
	case 3:
		return "all_element_but_wrong_place";
	case 4:
		return "wrong_end_character";
	case 5:
		return "modulo";
	default:
		throw "Unexpected index";
	}
}

INSTANTIATE_TEST_SUITE_P(
	test_string,
	Angle_Parsing,
	::testing::Values(
		std::make_tuple("45°31'13\"N"   ,true  , 45.520277777777778),
		std::make_tuple("45°31'13.4\"N" , true , 45.520388888888888),
		std::make_tuple("lol"           ,false , 0            ),
		std::make_tuple("°4531\"13.4N''",false , 0            ),
		std::make_tuple("45°31'13.4\"K" ,false , 0            ),
		std::make_tuple("360°00'0.0\"N", true  , 0.0          )),
		Angle_parsing_Test_Naming);