#ifndef CSV_READER_H
#define CSV_READER_H

#include <list>
#include <iostream>
#include <filesystem>
#include <string>

#include "includes/utils/daytime.h"
#include "submodule/logger/includes/exception.h"


class CSV_Reader
{
public:
    CSV_Reader() = delete;
    ~CSV_Reader();
    
    std::optional<std::list<std::string>> Next_Line();
    CSV_Reader(const std::filesystem::path& filepath);
private:
    std::ifstream m_file_stream;
    const char m_delimiter;

};

#endif //CSV_READER_H