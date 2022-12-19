#include "includes/ressource/csv_schedule_reader.h"
#include "includes/utils/exception_def.h"
#include "includes/network_optimizer/schedule.h"


Pair_station_TimeTable CSV_Schedule_Reader::Read_Schedule_File(std::filesystem::path filepath);
{
    CSV_Reader reader = CSV_Reader(filepath);
    std::vector<std::string> station_list;
    TimeTable time_table;
    while(std::optional<std::list<std::string>> line = reader.Next_Line())
    {
        if(*line.size()<2)
            THROW_TRACE(Reading_File_Error,"A line in the CSV file of the schedule is less than two");
        station_list.emplace_back(std::move((*line).front()));
        (*line).pop_front();
        std::vector temp_vector;
        while((*line).size())
        {
            temp_vector.emplace_back(std::move((*line).front()));
            (*line).pop_front();
        }
        time_table.emplace_back(std::move(temp_vector));

    }
    return Pair_station_TimeTable(station_list,time_table);
}