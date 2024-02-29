#include "includes/resource/csv/parser/station.h"

//utils
#include "includes/utils/exception_def.h"
#include "includes/coordinate/sphere.h"
#include "includes/utils/general.h"


std::vector<Network::Station> CSV::Parser::Station::Parse(const CSV::Engine::Parser& engine)
{
	std::vector<Network::Station> station_list;

	while (std::optional<std::vector<std::string>> line = engine.Next_Line())
	{
		if(line->size()!=3)
			THROW(READING_FILE_ERROR);
		
		//extract the three line
		std::string station_name = Generals::Trim_Space_Front_Back(std::move(line->at(0)));
		std::string latitude = Generals::Trim_Space_Front_Back(std::move(line->at(1)));
		std::string longitude = Generals::Trim_Space_Front_Back(std::move(line->at(2)));

		Coordinate::Spherical coord = Coordinate::Spherical::From_String(latitude,longitude);
		
		station_list.emplace_back(std::move(coord),std::move(station_name));
	}
	
	return station_list;
}