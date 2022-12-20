#include "includes/resource/csv_schedule_reader.h"

//utils
#include "includes/utils/exception_def.h"

//network
#include "includes/network_optimizer/schedule.h"


Pair_Station_TimeTable CSV_Schedule_Reader::Read_Schedule_File(const std::filesystem::path& filepath)
{
    CSV_Reader reader = CSV_Reader(filepath);
    std::vector<std::string> station_list;
    TimeTable time_table;
    while(std::optional<std::list<std::string>> line = reader.Next_Line())
    {
        if((*line).size()<2)
            THROW_TRACE(Reading_File_Error,"A line in the CSV file of the schedule is less than two");
        station_list.emplace_back(std::move((*line).front()));
        (*line).pop_front();
        std::vector<std::optional<DayTime>> temp_vector  ;
        while((*line).size())
        {
            std::optional<DayTime> value = DayTime::From_Time_String(std::move((*line).front()));
            temp_vector.emplace_back(value);
            (*line).pop_front();
        }
        time_table.emplace_back(std::move(temp_vector));

    }
    return Pair_Station_TimeTable(station_list,time_table);
}