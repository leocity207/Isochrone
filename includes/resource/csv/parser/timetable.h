#ifndef CSV_PARSER_TIMETABLE_H
#define CSV_PARSER_TIMETABLE_H

// Utils
#include "includes/utils/daytime.h"

// Ressource
#include "includes/resource/csv/engine/parser.h"

using  Pair_Station_TimeTable = std::pair<std::vector<std::string>, std::vector<std::vector<std::optional<DayTime>>>>;


namespace CSV
{
	namespace Parser
	{
		///////////////////////////////////////////////////
		/// @brief everything concerning parsing Timetables
		namespace Timetable
		{
			//////////////////////////////////////////////////////////////////////////
			/// @brief        Use the engine to pars the timetable data into a pair of stations and Timetable
			/// @param engine The CSV Engine used to parse the input CSV data
			/// @return       A pair of station inside the schedule and the timetable as a double vector
			Pair_Station_TimeTable Parse(const CSV::Engine::Parser& engine);
		};

	}; // Parser

}; // CSV


#endif //CSV_PARSER_TIMETABLE_H