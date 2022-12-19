#ifndef CSV_SCHEDULE_READER_H
#define CSV_SCHEDULE_READER_H

#include <vector>
#include <string>
#include <utility>

#include "includes/utils/daytime.h"
#include "includes/ressource/csv_reader.h"

typedef std::pair<std::vector<std::string>,std::vector<std::vector<DayTime>>> Pair_station_TimeTable;
class CSV_Schedule_Reader : public CSV_Reader
{
    public:
        static Pair_station_TimeTable Read_Schedule_File(std::filesystem::path filepath);
    private:
        CSV_Schedule_Reader() = delete;
};

#endif CSV_SCHEDULE_READER_H