#ifndef CSV_ENGINE_FILE_PARSER_H
#define CSV_ENGINE_FILE_PARSER_H

// STL
#include <filesystem>

// Resource
#include "parser.h"


namespace CSV
{
    namespace Engine
    {
        class File_Parser : public Parser
        {
            ////////
            /// CTOR
        public:
            File_Parser(std::filesystem::path&& path, const char delimiter);

            //////////////
            /// ATTRIBUTES
        private:
            std::filesystem::path m_filepath;
        };

    }; // Engine

}; // CSV


#endif //CSV_ENGINE_FILE_PARSER_H