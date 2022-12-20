#ifndef CSV_SCHEDULE_READER_H
#define CSV_SCHEDULE_READER_H

#include <vector>
#include <string>
#include <utility>
#include <filesystem>

#include "includes/utils/daytime.h"
#include "includes/resource/csv_reader.h"

typedef std::pair<std::vector<std::string>,std::vector<std::vector<std::optional<DayTime>>>> Pair_Station_TimeTable;

class CSV_Schedule_Reader : public CSV_Reader
{
    public:
        static Pair_Station_TimeTable Read_Schedule_File(const std::filesystem::path& filepath);
    private:
        CSV_Schedule_Reader() = delete;
};

#endif //CSV_SCHEDULE_READER_H