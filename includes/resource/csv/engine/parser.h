#ifndef CSV_ENGINE_PARSER_H
#define CSV_ENGINE_PARSER_H

// STM
#include <vector>
#include <string>
#include <optional>
#include <mutex>

// Utils
#include "includes/utils/owner.h"


namespace CSV
{
    namespace Engine
    {
        class Parser
        {
            ////////
            /// CTOR
        public:
            Parser() = delete;
            Parser(Memory::Owned<std::istream>&& stream, const char delimiter);

            ///////////
            /// METHODS
        public:
            std::optional<std::vector<std::string>> Next_Line() const;
        private:
            std::vector<std::string> Split_Line(std::string&& line) const noexcept;

            /////////////
            /// ATRIBUTES
        private:
            mutable Memory::Owned<std::istream> m_file_stream;
            const char m_delimiter;
            mutable std::mutex m_reader_mutex;
        };

    };//Engine

}; // CSV

#endif //CSV_ENGINE_PARSER_H