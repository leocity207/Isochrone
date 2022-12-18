#ifndef CSV_READER_H
#define CSV_READER_H

#include <vector>
#include <iostream>
#include <filesystem>
#include <string>

#include "includes/utils/daytime.h"
#include "submodule/logger/includes/exception.h"

constexpr size_t BLOCK_SIZE = 65536;

class CSV_Reader
{
protected:
    std::string Next_Line();
    static std::optional<std::string::iterator> Get_Next_Endl(std::string string);
    CSV_Reader() = delete;
    CSV_Reader(const std::filesystem::path& filepath);

private:
    std::ifstream m_file_stream;
    size_t m_length;
    size_t m_cursor;
    std::string m_leftover;
}

#endif