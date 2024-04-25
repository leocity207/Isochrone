#ifndef CSV_PARSER_STATION_H
#define CSV_PARSER_STATION_H

// Network
#include "includes/network/station.h"

// Ressource
#include "includes/resource/csv/engine/parser.h"


namespace CSV
{
	////////////////////////////////////////////////////////////////
	/// @brief Parsers are use to pars a CSV into some specific data
	namespace Parser
	{
		/////////////////////////////////////////////////
		/// @brief everything concerning parsing stations
		namespace Station
		{
			//////////////////////////////////////////////////////////////////////////
			/// @brief        Use the engine to pars the stations data into a list of Network::Station
			/// @param engine The CSV Engine used to parse the input CSV data
			/// @return       A list of stations
			std::vector<Network::Station> Parse(const CSV::Engine::Parser& engine);
		};

	}; // Parser

}; // CSV


#endif //CSV_PARSER_STATION_H