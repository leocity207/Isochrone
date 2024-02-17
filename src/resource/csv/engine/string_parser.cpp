#include "includes/resource/csv/engine/string_parser.h"
#include <sstream>


CSV::Engine::String_Parser::String_Parser(std::string&& data, const char delimiter) :
	CSV::Engine::Parser(std::make_unique<std::istringstream>(std::istringstream(std::move(data))), delimiter)
{
}