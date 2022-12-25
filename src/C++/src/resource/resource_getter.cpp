#include "includes/resource/resource_getter.h"

//STD
#include <iostream>

//utils
#include "includes/utils/exception_def.h"

//JSON parser
#include "submodule/rapidjson/include/rapidjson/istreamwrapper.h"
#include "submodule/rapidjson/include/rapidjson/document.h"
 
Resource_Getter::Resource_Getter(const std::filesystem::path& filesystem_path)
{
    std::ifstream config_file(filesystem_path);
    if(config_file.fail())
        THROW_TRACE(File_Open_Failed,"could not open file :" + filesystem_path.string())

    rapidjson::IStreamWrapper isw(config_file);
    rapidjson::Document document;
    document.ParseStream(isw);
    if(!document.HasMember("station file") && !document.HasMember("line list") && !document["station file"].IsString() && !document["line list"].IsArray())
        THROW_TRACE(Reading_File_Error,"config file is badly formated")
    m_path_to_Station_File = document["station file"].GetString();

    
    for(const auto& element : document["line list"].GetArray())
    {
        if(!element.HasMember("name") && !element.HasMember("schedules") && !element["name"].IsString()  && !element["schedules"].IsArray())
            THROW_TRACE(Reading_File_Error,"Line list are badly formatted")

        std::vector<std::filesystem::path> path_list;
        for(const auto& schedule : element["schedules"].GetArray())
        {
            if(!schedule.IsString())
                THROW_TRACE(Reading_File_Error,"Line list are badly formatted")
            path_list.emplace_back(schedule.GetString());
        }
        m_line_data.emplace_back(element["name"].GetString(),std::move(path_list));
    }
}

const std::filesystem::path& Resource_Getter::Get_Station_File() const noexcept
{
    return m_path_to_Station_File;
}

const std::vector<std::pair<std::string,std::vector<std::filesystem::path>>>& Resource_Getter::Get_Line_Files() const noexcept
{
    return m_line_data;
}