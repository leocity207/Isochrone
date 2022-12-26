#include "includes/resource/resource_getter.h"

//STD
#include <iostream>

//utils
#include "includes/utils/exception_def.h"

//JSON parser
#include "submodule/rapidjson/include/rapidjson/istreamwrapper.h"
#include "submodule/rapidjson/include/rapidjson/document.h"

//network
#include "includes/network_optimizer/line.h"

//helper function
const std::vector<std::pair<DayTemplate,std::filesystem::path>> Get_Schedules(const rapidjson::Value& json)
{
    if (!json.HasMember("paths") && !json.HasMember("paths") && !json["day_types"].IsString() && !json["day_types"].IsArray())
        THROW_TRACE(Reading_File_Error, "config file is badly formatted")
    std::vector<std::pair<DayTemplate, std::filesystem::path>> list;
    for (const auto& day_types : json["day_types"].GetArray())
    {
        if (!day_types.HasMember("days") && !day_types.HasMember("day_type") && !day_types["days"].IsArray() && !day_types["day_type"].IsArray())
            THROW_TRACE(Reading_File_Error, "Line list are badly formatted")

        std::array<bool, WEEKDAY_COUNT> day_list = {0};
        for (const auto& day: day_types["days"].GetArray())
        {
            if (day == "MONDAY")
                day_list[std::chrono::Monday.c_encoding()] = true;
            else if (day == "TUESDAY")
                day_list[std::chrono::Tuesday.c_encoding()] = true;
            else if (day == "WEDNESDAY")
                day_list[std::chrono::Wednesday.c_encoding()] = true;
            else if (day == "THURSDAY")
                day_list[std::chrono::Thursday.c_encoding()] = true;
            else if (day == "FRIDAY")
                day_list[std::chrono::Friday.c_encoding()] = true;
            else if (day == "SATURDAY")
                day_list[std::chrono::Saturday.c_encoding()] = true;
            else if (day == "SUNDAY")
                day_list[std::chrono::Sunday.c_encoding()] = true;
            else
                THROW_TRACE(Reading_File_Error, "Day does not exist")
        }
        std::array<bool, DAY_TYPE_COUNT> day_type_array;
        for (const auto& day_type: day_types["day_type"].GetArray())
        {
            if (day_type == "VACATION")
                day_type_array[VACATION_DAYS] = true;
            else if (day_type == "SCHOOL")
                day_type_array[SCHOOL_DAYS] = true;
            else if (day_type == "HOLIDAY")
                day_type_array[HOLYDAYS] = true;
            else if (day_type == "ALL")
                day_type_array = { true,true,true };
            else
                THROW_TRACE(Reading_File_Error, "Day type does not exist")
        }

        for (const auto& paths : json["paths"].GetArray())
        {
            list.emplace_back(DayTemplate(day_list, day_type_array), paths);
        }
    }
    return list;
}
Resource_Getter::Resource_Getter(const std::filesystem::path& filesystem_path)
{
    //open config file
    std::ifstream config_file(filesystem_path);
    if(config_file.fail())
        THROW_TRACE(File_Open_Failed,"could not open file :" + filesystem_path.string())

    //parth the config file
    rapidjson::IStreamWrapper isw(config_file);
    rapidjson::Document document;
    document.ParseStream(isw);

    //get the stations file
    if(!document.HasMember("station file") && !document.HasMember("line list") && !document["station file"].IsString() && !document["line list"].IsArray())
        THROW_TRACE(Reading_File_Error,"config file is badly formated")
    m_path_to_Station_File = document["station file"].GetString();

    //for all the lines
    for(const auto& element : document["line list"].GetArray())
    {
        if(!element.HasMember("name") && !element.HasMember("schedules") && !element["name"].IsString()  && !element["schedules"].IsArray())
            THROW_TRACE(Reading_File_Error,"Line list are badly formatted")

        //for all the schedules of the lines create the path to schedule file and the daytemplate tht it describe
        std::vector<std::pair<DayTemplate, std::filesystem::path>> path_list;
        for(const auto& schedule : element["schedules"].GetArray())
        {
            const std::vector<std::pair<DayTemplate, std::filesystem::path>> schedules = Get_Schedules(schedule);
            path_list.insert(path_list.end(),std::make_move_iterator(schedules.begin()),std::make_move_iterator(schedules.end()));
        }
     
        //add the above data to the lines data and don't forget to add the name of the line
        m_line_data.emplace_back(element["name"].GetString(),std::move(path_list));
    }
}

const std::filesystem::path& Resource_Getter::Get_Station_File() const noexcept
{
    return m_path_to_Station_File;
}

const std::vector<std::pair<std::string, std::vector<std::pair<DayTemplate, std::filesystem::path>>>>& Resource_Getter::Get_Line_Files() const noexcept
{
    return m_line_data;
}