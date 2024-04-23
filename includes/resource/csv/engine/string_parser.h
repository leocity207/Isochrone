#ifndef CSV_ENGINE_STRING_PARSER_H
#define CSV_ENGINE_STRING_PARSER_H

// Resource
#include "parser.h"

// Utils
#include "includes/utils/ctor.h"

namespace CSV
{
	namespace Engine
	{
		/////////////////////////////////////////////////////
		/// @brief base class for parsing a CSV Stringstream
		/// @note  default_constructible
		///        not_copy_constructible
		///        not_copy_assignable
		///        move_constructible
		///        move_asignable
		class String_Parser : public Parser
		{
			//#####
			// CTOR
		public:
			DELETE_DEFAULT_CTOR(String_Parser);
			DELETE_COPY(String_Parser);
			DEFAULT_MOVE(String_Parser);

			////////////////////////////////////////////////////
			/// @brief Explicit constructor by move construction
			String_Parser(std::string&& str, const char delimiter);
		};

	}; //Engine

}; //CSV


#endif //CSV_ENGINE_STRING_PARSER_H