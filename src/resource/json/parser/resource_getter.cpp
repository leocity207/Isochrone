#include "includes/resource/json/parser/resource_getter.h"

// Utils
#include "includes/utils/exception_def.h"

// JSON parser
#include "submodule/rapidjson/include/rapidjson/istreamwrapper.h"
#include "submodule/rapidjson/include/rapidjson/document.h"

// Network
#include "includes/network/day_info.h"


/////////////////
//helper function
static std::vector<std::pair<Network::DayTemplate,std::filesystem::path>> Get_Schedules(const rapidjson::Value& json)
{
	if (!json.HasMember("paths") && !json.HasMember("day template") && !json["paths"].IsArray() && !json["day template"].IsArray())
		THROW(READING_FILE_ERROR)
	std::vector<std::pair<Network::DayTemplate, std::filesystem::path>> list;
	for (const auto& day_types : json["day template"].GetArray())
	{
		if (!day_types.HasMember("weekdays") && !day_types.HasMember("type") && !day_types["weekdays"].IsArray() && !day_types["type"].IsArray())
			THROW(READING_FILE_ERROR)

		std::array<bool, Network::WEEKDAY_COUNT> day_list = {0};
		for (const auto& day: day_types["weekdays"].GetArray())
		{
			// !!! carefull monday map to 6 and sunday to 0 !!!
			if (std::string_view(day.GetString()) == "MONDAY")
				day_list[std::chrono::Monday.c_encoding()] = true;
			else if (std::string_view(day.GetString()) == "TUESDAY")
				day_list[std::chrono::Tuesday.c_encoding()] = true;
			else if (std::string_view(day.GetString()) == "WEDNESDAY")
				day_list[std::chrono::Wednesday.c_encoding()] = true;
			else if (std::string_view(day.GetString()) == "THURSDAY")
				day_list[std::chrono::Thursday.c_encoding()] = true;
			else if (std::string_view(day.GetString()) == "FRIDAY")
				day_list[std::chrono::Friday.c_encoding()] = true;
			else if (std::string_view(day.GetString()) == "SATURDAY")
				day_list[std::chrono::Saturday.c_encoding()] = true;
			else if (std::string_view(day.GetString()) == "SUNDAY")
				day_list[std::chrono::Sunday.c_encoding()] = true;
			else if (std::string_view(day.GetString()) == "ALL")
				day_list = { true,true,true,true,true,true,true};
			else
				THROW(READING_FILE_ERROR)
		}
		std::array<bool, Network::DAY_TYPE_COUNT> day_type_array = {0};
		for (const auto& day_type: day_types["type"].GetArray())
		{
			if (std::string_view(day_type.GetString()) == "VACATION")
				day_type_array[Network::VACATION_DAYS] = true;
			else if (std::string_view(day_type.GetString()) == "SCHOOL")
				day_type_array[Network::SCHOOL_DAYS] = true;
			else if (std::string_view(day_type.GetString()) == "HOLIDAY")
				day_type_array[Network::HOLYDAYS] = true;
			else if (std::string_view(day_type.GetString()) == "ALL")
				day_type_array = { true,true,true };
			else
				THROW(READING_FILE_ERROR)
		}

		for (const auto& paths : json["paths"].GetArray())
			list.emplace_back(std::move(Network::DayTemplate(day_list, day_type_array)),std::move(paths.GetString()));
	}
	return list;
}

JSON::Parser::Resource_Getter::Resource_Getter(std::istream&& stream)
{
	if(stream.fail())
		THROW(FILE_OPEN_FAILED)

	//parth the config file
	rapidjson::IStreamWrapper isw(stream);
	rapidjson::Document document;
	document.ParseStream(isw);

	//get the stations file
	if(!document.HasMember("station file") && !document.HasMember("line list") && !document["station file"].IsString() && !document["line list"].IsArray())
		THROW(READING_FILE_ERROR)
	m_path_to_Station_File = document["station file"].GetString();

	//for all the lines
	for(const auto& element : document["line list"].GetArray())
	{
		if(!element.HasMember("name") && !element.HasMember("schedules") && !element["name"].IsString()  && !element["schedules"].IsArray())
			THROW(READING_FILE_ERROR)

		//for all the schedules of the lines create the path to schedule file and the daytemplate tht it describe
		std::vector<std::pair<Network::DayTemplate, std::filesystem::path>> path_list = {};
		for(const auto& schedule : element["schedules"].GetArray())
		{
			std::vector<std::pair<Network::DayTemplate, std::filesystem::path>> schedules = Get_Schedules(schedule);
			std::move(schedules.begin(), schedules.end(), std::back_inserter(path_list));
		}
	 
		//add the above data to the lines data and don't forget to add the name of the line
		m_line_data.emplace_back(element["name"].GetString(),std::move(path_list));
	}
}

std::filesystem::path&& JSON::Parser::Resource_Getter::Get_Station_File() noexcept
{
	return std::move(m_path_to_Station_File);
}

std::vector<std::pair<std::string, std::vector<std::pair<Network::DayTemplate, std::filesystem::path>>>>&& JSON::Parser::Resource_Getter::Get_Line_Files() noexcept
{
	return std::move(m_line_data);
}