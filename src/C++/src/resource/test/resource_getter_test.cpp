#include "resource_getter_test.h"

#include "includes/resource/resource_getter.h"
#include "includes/network_optimizer/day_info.h"


TEST_F(Resource_Getter_Test, test)
{
	std::filesystem::path path_to_csv = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/resource/test/config_test.json";

	Resource_Getter getter(path_to_csv);

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