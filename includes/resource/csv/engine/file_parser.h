#ifndef CSV_ENGINE_FILE_PARSER_H
#define CSV_ENGINE_FILE_PARSER_H

// STL
#include <filesystem>

// Resource
#include "parser.h"

// Utils
#include "includes/utils/ctor.h"



namespace CSV
{
	namespace Engine
	{
		/////////////////////////////////////////////////////
		/// @brief base class for parsing a CSV File
		/// @note  default_constructible
		///        not_copy_constructible
		///        not_copy_assignable
		///        move_constructible
		///        move_asignable
		class File_Parser : public Parser
		{
			//#####
			// CTOR
		public:
			DELETE_DEFAULT_CTOR(File_Parser)
			DELETE_COPY(File_Parser)
			DEFAULT_MOVE(File_Parser)

			////////////////////////////////////////////////////
			/// @brief Explicit constructor by move construction
			File_Parser(std::filesystem::path&& path, const char delimiter);

			//###########
			// ATTRIBUTES
		private:
			std::filesystem::path m_filepath;
		};

	}; // Engine

}; // CSV


#endif //CSV_ENGINE_FILE_PARSER_H