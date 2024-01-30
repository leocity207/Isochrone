#ifndef CSV_PARSER_TIMETABLE_H
#define CSV_PARSER_TIMETABLE_H


#include "includes/utils/daytime.h"
#include "includes/resource/csv/engine/parser.h"

using  Pair_Station_TimeTable = std::pair<std::vector<std::string>, std::vector<std::vector<std::optional<DayTime>>>>;

namespace CSV
{
    namespace Parser
    {
        namespace Timetable
        {
            Pair_Station_TimeTable Parse(const CSV::Engine::Parser& engine);
        };
    };
};
#endif //CSV_PARSER_TIMETABLE_H