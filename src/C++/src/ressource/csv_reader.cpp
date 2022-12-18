
#include <vector>
#include <filesystem>
#include <algorithm>

#include "includes/utils/daytime.h"
#include "includes/utils/exception_def.h"
#include "includes/ressource/csv_reader.h"



CSV_Reader::CSV_Reader(const std::filesystem::path& filepath) : m_cursor(0),m_leftover()
{
    m_file_stream = std::ifstream(filepath, std::ios::in);
    if(m_file_stream.fail())
        THROW_TRACE(File_Open_Failed,"could not open file :" + filepath.u8string())

    m_file_stream.seekg (0, m_file_stream.end);
    m_length = m_file_stream.tellg();
    m_file_stream.seekg (0, m_file_stream.beg);
}

std::optional<std::string> CSV_Reader::Next_Line()
{
// A check to see if we read the whole file already
if(m_cursor>m_length)
    return std::nullopt;

std::string to_return;
std::string::const_iterator endl_pos = std::find(m_leftover.begin(),m_leftover.end(),"\n");
if(endl_pos != m_leftover.end()) // if we found an "\n" inside the leftover we don't need to read a new block, just return the part
{
    std::string buffer;
    std::move(m_leftover.begin(),endl_pos,std::back_inserter(to_return));
    std::move(endl_pos,buffer,std::back_inserter(buffer));
    m_leftover.clear();
    m_leftover = std::move(buffer);
    return std::move(to_return);
}

//we didn't found the next "\n" inside the leftover so we need to read new block
to_return = std::move(m_leftover);
m_leftover.clear();
size_t length_to_read = std::min(m_length-m_cursor,BLOCK_SIZE);
m_leftover.resize(length_to_read,"\0")
if(!m_file_stream.read(&m_leftover[0], length_to_read))
    throw Reading_File_Error();
m_cursor+=length_to_read;

//recursivly look for the "\n" character
return to_return + this->Next_Line().value_or("");
}

std::optional<std::string> CSV_Reader::Next_Line()
{
    // A check to see if we read the whole file already
    if (m_cursor > m_length)
        return std::nullopt;

    std::string to_return;
    std::string buffer;
    buffer.reserve(BLOCK_SIZE); // preallocate buffer to a reasonable size

    // Keep reading blocks of data from the file until we find a newline character or reach the end of the file
    while (true)
    {
        // Read a block of data from the file
        buffer.resize(BLOCK_SIZE);
        if (!m_file_stream.read(&buffer[0], BLOCK_SIZE))
            throw Reading_File_Error();

        // Update the cursor and check if we reached the end of the file
        m_cursor += BLOCK_SIZE;
        if (m_cursor >= m_length)
        {
            // Append the entire buffer to the leftover string and return it
            to_return += std::move(buffer);
            m_leftover = std::move(to_return);
            return std::move(m_leftover);
        }

        // Look for a newline character in the buffer
        std::string::const_iterator endl_pos = std::find(buffer.begin(), buffer.end(), '\n');
        if (endl_pos != buffer.end())
        {
            // Extract the portion of the buffer up to and including the newline character
            std::string line;
            std::move(buffer.begin(), endl_pos, std::back_inserter(line));

            // Store the rest of the buffer in the leftover string
            std::move(endl_pos, buffer.end(), std::back_inserter(m_leftover));
            return std::move(line);
        }

        // No newline character was found, so append the buffer to the leftover string and continue reading
        to_return += std::move(buffer);
    }
}

