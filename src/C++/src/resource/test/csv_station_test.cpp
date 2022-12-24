#include "csv_station_test.h"

#include "includes/resource/csv_station_reader.h"

TEST_F(CSV_Station_Test, reading_test)
{
	std::filesystem::path path_to_csv = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/resource/test/test_station.csv";

	std::vector<Station> station_list = CSV_Station_Reader::Read_Station_File(path_to_csv);

	ASSERT_EQ(station_list.size(), 3);

	ASSERT_EQ(station_list[0].Get_Name(), "Station1");
	ASSERT_EQ(station_list[1].Get_Name(), "station2");
	ASSERT_EQ(station_list[2].Get_Name(), "station3");

	ASSERT_EQ(station_list[0].GetCoordinate(), Sphere_Coordinate("45°31'13\"N", "45°31'13\"E"));
	ASSERT_EQ(station_list[0].GetCoordinate(), Sphere_Coordinate("45°31'13\"N", "45°31'13\"E"));
	ASSERT_EQ(station_list[0].GetCoordinate(), Sphere_Coordinate("45°31'13\"N", "45°31'13\"E"));
}