#include "includes/resource/csv/parser/timetable.h"

// Utils
#include "includes/utils/exception_def.h"
#include "includes/utils/general.h"

// Network
#include "includes/network/schedule.h"

// Stl
#include <span>


Pair_Station_TimeTable CSV::Parser::Timetable::Parse(const CSV::Engine::Parser& engine)
{
	std::vector<std::string> station_list;
	Network::TimeTable time_table;
	size_t registered_size = 0;

	while(std::optional<std::vector<std::string>> line = engine.Next_Line())
	{
		// if less than the station cholumn and one line there is a problem
		if (!registered_size)
			registered_size = line->size();
		if(line->size()<2)
			THROW(READING_FILE_ERROR)
		else if(registered_size != line->size())
			THROW(READING_FILE_ERROR)
		

		//add the station to the list of station
		std::string_view station_view = Generals::Trim_Space_Front_Back(line->front());
		if (station_view.size() == 0)
			THROW(READING_FILE_ERROR);
		station_list.emplace_back(Generals::Trim_Space_Front_Back(line->front()));

		//read all the daytimes
		std::vector<std::optional<DayTime>> temp_vector;
		for(std::string& element: std::span(++(line->begin()),line->end()))
			temp_vector.emplace_back(DayTime::From_Time_String(element));
		time_table.emplace_back(std::move(temp_vector));
	}

	
	return Pair_Station_TimeTable(station_list, time_table);
}