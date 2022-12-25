#include "resource_getter_test.h"

#include "includes/resource/resource_getter.h"


TEST_F(Resource_Getter_Test, test)
{
	std::filesystem::path path_to_csv = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/resource/test/config_test.json";

	Resource_Getter getter(path_to_csv);

	ASSERT_EQ(getter.Get_Station_File(),"Geographie/coordinate.csv");

	std::vector<std::pair<std::string, std::vector<std::filesystem::path>>> truc = getter.Get_Line_Files();
	EXPECT_EQ(truc.size(), 1);
	EXPECT_EQ(truc[0].first, "Ligne 1");

	EXPECT_EQ(truc[0].second.size(), 4);
	EXPECT_EQ(truc[0].second[0], "Ligne 1/line_1_a_6t_12345v.csv");
	EXPECT_EQ(truc[0].second[1], "Ligne 1/line_1_a_12345s.csv");
	EXPECT_EQ(truc[0].second[2], "Ligne 1/line_1_r_6t_12345v.csv");
	EXPECT_EQ(truc[0].second[3], "Ligne 1/line_1_r_12345s.csv");
}