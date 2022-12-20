#ifndef CSV_STATION_READER_H
#define CSV_STATION_READER_H

#include "includes/resource/csv_reader.h"
#include "includes/network_optimizer/station.h"

class CSV_Station_Reader : public CSV_Reader
{
    public:
        static std::vector<Station> Read_Station_File(const std::filesystem::path& filepath);
    private:
        CSV_Station_Reader() = delete;
};

#endif CSV_STATION_READER_H