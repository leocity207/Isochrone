
#include "includes/resource/csv/parser/station.h"

//utils
#include "includes/utils/exception_def.h"
#include "includes/utils/coordinate_2d.h"
#include "includes/utils/general.h"


std::vector<::Station> CSV::Parser::Station::Parse(const CSV::Engine::Parser& engine)
{
    std::vector<::Station> station_list;

    while (std::optional<std::vector<std::string>> line = engine.Next_Line())
    {
        if(line->size()!=3)
            THROW_TRACE(READING_FILE_ERROR,"A line in the CSV file of the schedule is less than three");
        
        //extract the three line
        std::string station_name = Generals::Trim_Space_Front_Back(std::move(line->at(0)));
        std::string latitude = Generals::Trim_Space_Front_Back(std::move(line->at(1)));
        std::string longitude = Generals::Trim_Space_Front_Back(std::move(line->at(2)));

        Sphere_Coordinate coord = Sphere_Coordinate(latitude,longitude);
        
        station_list.emplace_back(std::move(coord),std::move(station_name));
    }
    
    return station_list;
}