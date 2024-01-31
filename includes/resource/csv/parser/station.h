#ifndef CSV_PARSER_STATION_H
#define CSV_PARSER_STATION_H

#include "includes/network_optimizer/station.h"
#include "includes/resource/csv/engine/parser.h"

namespace CSV
{
    namespace Parser
    {
        namespace Station
        {
            std::vector<::Station> Parse(const CSV::Engine::Parser& engine);
        };
    };
};

#endif //CSV_PARSER_STATION_H