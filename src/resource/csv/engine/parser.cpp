
#include "includes/resource/csv/engine/parser.h"

#include <algorithm>

#include "includes/utils/daytime.h"
#include "includes/utils/exception_def.h"



CSV::Engine::Parser::Parser(Memory::Owned<std::istream>&& stream, const char delimiter) :
	m_delimiter(delimiter),
	m_file_stream(std::move(stream))
{
}

std::optional<std::vector<std::string>> CSV::Engine::Parser::Next_Line() const
{
	// Get the line
	std::string line;
	{
		const std::lock_guard<std::mutex> lock(m_reader_mutex);
		if (!std::getline(*m_file_stream, line))
		{
			if (m_file_stream->eof())
				return std::nullopt;
			else
				throw READING_FILE_ERROR();
		}
	}
	
	return CSV::Engine::Parser::Split_Line(std::move(line));
}

std::vector<std::string> CSV::Engine::Parser::Split_Line(std::string&& line) const noexcept
{
	std::vector<std::string> chunks;
	std::string::iterator chunk_start = line.begin();
	std::string::iterator chunk_end = line.begin();
	// move each chunk of the data insZide the line to the vector
	while (chunk_end != line.end()) {
		chunk_end = std::find(chunk_start, line.end(), m_delimiter);
		std::string chunk;
		chunk.assign(std::make_move_iterator(chunk_start), std::make_move_iterator(chunk_end));
		chunks.emplace_back(std::move(chunk));
		chunk_start = chunk_end;
		if(chunk_end != line.end())
			chunk_start++;
	}
	return chunks;
}

