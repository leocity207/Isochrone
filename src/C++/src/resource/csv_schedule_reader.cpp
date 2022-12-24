#include "includes/resource/csv_schedule_reader.h"

//utils
#include "includes/utils/exception_def.h"
#include "includes/utils/general.h"

//network
#include "includes/network_optimizer/schedule.h"


Pair_Station_TimeTable CSV_Schedule_Reader::Read_Schedule_File(const std::filesystem::path& filepath)
{
    CSV_Reader reader = CSV_Reader(filepath);
    std::vector<std::string> station_list;
    TimeTable time_table;

    while(std::optional<std::list<std::string>> line = reader.Next_Line())
    {
        // if less than the station cholumn and one line there is a problem
        if(line->size()<2)
            THROW_TRACE(Reading_File_Error,"A line in the CSV file of the schedule is less than two");

        //add the station to the list of station
        std::string_view station_view = Generals::Trim_Space_Front_Back(line->front());
        if (station_view.size() == 0)
            THROW_TRACE(Reading_File_Error, "The  station_name of a line is incorrect");
        station_list.emplace_back(Generals::Trim_Space_Front_Back(line->front()));
        line->pop_front();

        //read all the daytimes
        std::vector<std::optional<DayTime>> temp_vector;
        while((*line).size())
        {
            std::optional<DayTime> value = DayTime::From_Time_String(line->front());
            temp_vector.emplace_back(value);
            line->pop_front();
        }
        time_table.emplace_back(std::move(temp_vector));
    }
    return Pair_Station_TimeTable(station_list,time_table);
}