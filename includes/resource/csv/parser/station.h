#ifndef CSV_PARSER_STATION_H
#define CSV_PARSER_STATION_H

// Network
#include "includes/network/station.h"

// Ressource
#include "includes/resource/csv/engine/parser.h"


namespace CSV
{
	namespace Parser
	{
		namespace Station
		{
			std::vector<Network::Station> Parse(const CSV::Engine::Parser& engine);
		};

	}; // Parser

}; // CSV

#endif //CSV_PARSER_STATION_H