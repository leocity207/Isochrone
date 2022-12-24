#include "csv_schedule_test.h"

#include "includes/resource/csv_schedule_reader.h"


TEST_F(CSV_Schedule_Test, reading_test)
{
	std::filesystem::path path_to_csv = "C:/Users/Leocl/Documents/Isochrone/src/C++/src/resource/test/test_schedule.csv";

	auto [station,timetable] = CSV_Schedule_Reader::Read_Schedule_File(path_to_csv);

	ASSERT_EQ(station.size(), 3);
    ASSERT_EQ(timetable.size(), 3);
    ASSERT_EQ(timetable[0].size(), 2);
    

	ASSERT_EQ(station[0], "Station1");
	ASSERT_EQ(station[1], "station2");
	ASSERT_EQ(station[2], "station3");

	ASSERT_EQ(timetable[0][0], DayTime(std::chrono::hours(7),std::chrono::minutes(10)));
	ASSERT_EQ(timetable[0][1], DayTime(std::chrono::hours(10),std::chrono::minutes(20)));

    ASSERT_EQ(timetable[1][0], DayTime(std::chrono::hours(7),std::chrono::minutes(20)));
	ASSERT_EQ(timetable[1][1], DayTime(std::chrono::hours(10),std::chrono::minutes(30)));

    ASSERT_EQ(timetable[2][0], DayTime(std::chrono::hours(7),std::chrono::minutes(30)));
	ASSERT_EQ(timetable[2][1], DayTime(std::chrono::hours(10),std::chrono::minutes(40)));
}