#ifndef CSV_ENGINE_STRING_PARSER_H
#define CSV_ENGINE_STRING_PARSER_H

#include "parser.h"

namespace CSV
{
    namespace Engine
    {
        class String_Parser : public Parser
        {
            ////////
            /// CTOR
        public:
            String_Parser(std::string&& str, const char delimiter);
        };
    }; //Engine
}; //CSV

#endif //CSV_ENGINE_STRING_PARSER_H