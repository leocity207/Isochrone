#include "resource_getter_test.h"

#include "includes/resource/json/parser/resource_getter.h"
#include "includes/network_optimizer/day_info.h"


TEST_F(Resource_Getter_Test, test)
{
	std::istringstream string_stream("{\"station file\":\"test.csv\",\"line list\":[{\"name\":\"Ligne 1\",\"schedules\": [{\"paths\": [\"a.csv\",\"b.csv\"],\"day template\": [{\"weekdays\": [ \"MONDAY\", \"TUESDAY\", \"WEDNESDAY\", \"THURSDAY\", \"FRIDAY\" ],\"type\": [ \"VACATION\" ]},{\"weekdays\": [ \"SATURDAY\" ],\"type\": [ \"ALL\" ]}]},{\"paths\": [\"c.csv\",\"d.csv\"],\"day template\": [{\"weekdays\": [ \"MONDAY\", \"TUESDAY\", \"WEDNESDAY\", \"THURSDAY\", \"FRIDAY\" ],\"type\": [ \"SCHOOL\" ]}]}]}]}");

	JSON::Parser::Resource_Getter getter(std::move(string_stream));

	ASSERT_EQ(getter.Get_Station_File(), "test.csv");

	const auto& truc = getter.Get_Line_Files();

	//line 
	EXPECT_EQ(truc.size(), 1);
	EXPECT_EQ(truc[0].first, "Ligne 1");

	EXPECT_EQ(truc[0].second.size(), 6);

	EXPECT_EQ(truc[0].second[0].second, "a.csv");
	EXPECT_EQ(truc[0].second[1].second, "b.csv");
	EXPECT_EQ(truc[0].second[2].second, "a.csv");
	EXPECT_EQ(truc[0].second[3].second, "b.csv");
	EXPECT_EQ(truc[0].second[4].second, "c.csv");
	EXPECT_EQ(truc[0].second[5].second, "d.csv");


	EXPECT_EQ(truc[0].second[0].first, DayTemplate({ 0,1,1,1,1,1,0 }, { 0,1,0 }));
	EXPECT_EQ(truc[0].second[1].first, DayTemplate({ 0,1,1,1,1,1,0 }, { 0,1,0 }));
	EXPECT_EQ(truc[0].second[2].first, DayTemplate({ 0,0,0,0,0,0,1 }, { 1,1,1 }));
	EXPECT_EQ(truc[0].second[3].first, DayTemplate({ 0,0,0,0,0,0,1 }, { 0,1,0 }));
	EXPECT_EQ(truc[0].second[4].first, DayTemplate({ 0,1,1,1,1,1,0 }, { 1,0,0 }));
	EXPECT_EQ(truc[0].second[5].first, DayTemplate({ 0,1,1,1,1,1,0 }, { 1,0,0 }));

}