#include "includes/resource/csv/engine/file_parser.h"

#include <fstream>
#include <memory>

CSV::Engine::File_Parser::File_Parser(std::filesystem::path&& path, const char delimiter) :
	CSV::Engine::Parser(std::make_unique<std::ifstream>(std::ifstream(path)), delimiter),
	m_filepath(std::move(path))
{
}