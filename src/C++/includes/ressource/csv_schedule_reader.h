#ifndef CSV_SCHEDULE_READER_H
#define CSV_SCHEDULE_READER_H

#include "includes/ressource/csv_reader.h"

class CSV_Schedule_Reader : public CSV_Reader
{
    static std::vector<std::vector<DayTime>> Read_Schedule_File(std::filesystem::path filepath);
};
#endif CSV_SCHEDULE_READER_H