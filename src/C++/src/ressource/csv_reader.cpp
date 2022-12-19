
#include <vector>
#include <filesystem>
#include <algorithm>

#include "includes/utils/daytime.h"
#include "includes/utils/exception_def.h"
#include "includes/ressource/csv_reader.h"



CSV_Reader::CSV_Reader(const std::filesystem::path& filepath) : m_delimiter('\n')
{
    m_file_stream = std::ifstream(filepath, std::ios::in);
    if(m_file_stream.fail())
        THROW_TRACE(File_Open_Failed,"could not open file :" + filepath.string())
}

std::optional<std::list<std::string>> CSV_Reader::Next_Line()
{
    // Get the line
    std::string line;
    if(!std::getline(m_file_stream,line))
    {
        if(m_file_stream.eof())
        {
            return std::nullopt;
        }
        else
        {
            throw Reading_File_Error();
        }
    }
    
    std::list<std::string> chunks;
    std::string chunk;
    auto start = line.begin();
    auto end = line.begin();
    // move each chunk of the data inside the line to the vector
    while (end != line.end()) {
        end = std::find(start, line.end(), m_delimiter);
        chunk.assign(std::make_move_iterator(start), std::make_move_iterator(end));
        chunks.emplace_back(std::move(chunk));
        start = end;
        if (start != line.end()) {
            ++start;
        }
    }
    // check for the small leftover at the end of the string
    if (start != line.end()) {
        chunk.assign(std::make_move_iterator(start), std::make_move_iterator(line.end()));
        chunks.emplace_back(std::move(chunk));
    }
    return chunks;
}

