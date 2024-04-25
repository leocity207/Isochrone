#ifndef JSON_PARSER_RESOURCE_CONFIG_H
#define JSON_PARSER_RESOURCE_CONFIG_H

// STL
#include <filesystem>

namespace Network {
    class DayTemplate;
}


namespace JSON
{
    namespace Parser
    {
        ////////////////////////////////////////////////////////////////////////
        /// @brief this class implement a resource getter for a specific network
        class Resource_Getter
        {

        public:

            //////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief constructor
            /// @param filesystem_path path to the config file wich indicate how too look for the station data 
            Resource_Getter(std::istream&& filesystem_path);

            //////////////////////////////////////////////////
            /// @brief give back the path to the station files
            std::filesystem::path&& Get_Station_File() noexcept;

            ///////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief give back the path to the timetables files and all the informations that are needed
            std::vector<std::pair<std::string, std::vector<std::pair<Network::DayTemplate, std::filesystem::path>>>>&& Get_Line_Files() noexcept;
        private:
            std::filesystem::path m_path_to_Station_File;
            std::vector<std::pair<std::string, std::vector<std::pair<Network::DayTemplate, std::filesystem::path>>>> m_line_data;
        };

    }//Parser

};//JSON


#endif //JSON_PARSER_RESOURCE_CONFIG_H