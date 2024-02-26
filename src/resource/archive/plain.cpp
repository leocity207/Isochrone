#include "includes/resource/archive/plain.h"

// Utils
#include "includes/utils/general.h"

// Ressrouce
#include "includes/resource/csv/engine/file_parser.h"
#include "includes/resource/csv/parser/station.h"
#include "includes/resource/csv/parser/timetable.h"
#include "includes/resource/json/parser/resource_getter.h"

// Valididator
#include "includes/resource/csv/validator/timetable.h"

static void Check_Timetable(const TimeTable& timetable,const std::string& timetable_name)
{
	const auto errors = CSV::Parser::Validator::Validate(Generals::Transpose(timetable), timetable_name);
	if (!errors.empty())
	{
		for (const auto& error : errors)
			TRACE(error->Get_Error_As_String());
		THROW(TIMETABLE_BADLY_FORMATED);
	}
}

std::pair<std::vector<Network::Station>, std::vector<Network::Scheduled_Line>> Resource::Archive::Plaine::Parse_Scheduled_Network_Resource(std::filesystem::path&& plain_archive_path)
{
	std::ifstream stream(plain_archive_path);
	JSON::Parser::Resource_Getter getter(std::move(stream));

	CSV::Engine::File_Parser parser(plain_archive_path.parent_path() / getter.Get_Station_File(), ';');
	std::vector<Network::Station> stations = std::move(CSV::Parser::Station::Parse(parser));
	std::vector<Network::Scheduled_Line> scheduled_lines;

	for (auto& line_parse_data : getter.Get_Line_Files())
	{
		std::vector<Network::Schedule> schedules;
		for (auto& schedule : line_parse_data.second)
		{
			CSV::Engine::File_Parser timetable_parser(plain_archive_path.parent_path() / schedule.second, ';');
			auto [station_list, timetable] = CSV::Parser::Timetable::Parse(timetable_parser);
			
			Check_Timetable(timetable, schedule.second.string());

			std::vector<Network::Station_CRef> tmp_station_reference;
			for (const std::string& station_name : station_list)
				tmp_station_reference.emplace_back(Network::Station::Get_Station_By_Name(stations, station_name));

			schedules.emplace_back(std::move(tmp_station_reference), std::move(timetable), std::move(schedule.first), line_parse_data.first+schedule.second.filename().string());
		}
		scheduled_lines.emplace_back(std::move(schedules), std::move(line_parse_data.first));
	}
	return std::make_pair(std::move(stations), std::move(scheduled_lines));
}