
#include "includes/resource/csv_station_reader.h"

//utils
#include "includes/utils/exception_def.h"
#include "includes/utils/coordinate_2d.h"
#include "includes/utils/general.h"


std::vector<Station> CSV_Station_Reader::Read_Station_File(const std::filesystem::path& filepath)
{
    std::vector<Station> station_list;
    CSV_Reader reader = CSV_Reader(filepath);

    while(std::optional<std::list<std::string>> line = reader.Next_Line())
    {
        if(line->size()!=3)
            THROW_TRACE(Reading_File_Error,"A line in the CSV file of the schedule is less than three");
        
        //extract the three line
        std::string station_name = Generals::Trim_Space_Front_Back(std::move((*line).front()));
        (*line).pop_front();
        std::string latitude = Generals::Trim_Space_Front_Back(std::move((*line).front()));
        (*line).pop_front();
        std::string longitude = Generals::Trim_Space_Front_Back(std::move((*line).front()));
        (*line).pop_front();

        Sphere_Coordinate coord = Sphere_Coordinate(latitude,longitude);
        
        station_list.emplace_back(std::move(coord),std::move(station_name));
    }
    
    return station_list;
}