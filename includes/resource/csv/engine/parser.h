#ifndef CSV_ENGINE_PARSER_H
#define CSV_ENGINE_PARSER_H

// STM
#include <vector>
#include <string>
#include <optional>
#include <mutex>

// Utils
#include "includes/utils/owner.h"
#include "includes/utils/ctor.h"

/////////////////////////////////////////////////////
/// @brief Everything revolving around the CSV Format
namespace CSV
{
	////////////////////////////////////////////////////
	/// @brief Engines are use to decode or encode into the CSV Format
	namespace Engine
	{
		/////////////////////////////////////////////////////
		/// @brief base class for parsing a CSV Stream of data
		/// @note  default_constructible
		///        not_copy_constructible
		///        not_copy_assignable
		///        move_constructible
		///        move_asignable
		class Parser
		{
			//#####
			// CTOR
		public:
			DELETE_DEFAULT_CTOR(Parser);
			DELETE_COPY(Parser);
			DEFAULT_MOVE(Parser);

			//////////////////////////////////////////////////////////////
			/// @brief          Explicit constructor by move construction
			/// @param stream   A stream where to parse the CSV from
			/// @pram delimiter The CSV delimiter character between input
			Parser(Memory::Owned<std::istream>&& stream, const char delimiter);

			//########
			// METHODS
		public:
			std::optional<std::vector<std::string>> Next_Line() const;
		private:
			std::vector<std::string> Split_Line(std::string&& line) const noexcept;

			//##########
			// ATRIBUTES
		private:
			mutable Memory::Owned<std::istream> m_file_stream;
			const char m_delimiter;
			mutable std::mutex m_reader_mutex;
		};

	};//Engine

}; // CSV


#endif //CSV_ENGINE_PARSER_H