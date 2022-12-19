#include "includes/ressource/csv_station_reader.h"
#include "includes/utils/exception_def.h"


std::vector<Station> CSV_Station_Reader::Read_Station_File(std::filesystem::path filepath)
{
    std::vector<Station> station_list;
    CSV_Reader reader = CSV_Reader(filepath);

    while(std::optional<std::list<std::string>> line = reader.Next_Line())
    {
        if(line->size()!=3)
            THROW_TRACE(Reading_File_Error,"A line in the CSV file of the schedule is less than three");
        

    }
    return station_list;
}