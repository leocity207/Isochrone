#include "includes/resource/archive/plain.h"

#include "includes/resource/csv/parser/station.h"
#include "includes/resource/csv/parser/timetable.h"

#include "includes/resource/json/parser/resource_getter.h"

#include "includes/resource/csv/engine/file_parser.h"


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
			std::vector<Network::Station_CRef> tmp_station_reference;
			for (const std::string& station_name : station_list)
				tmp_station_reference.emplace_back(Network::Station::Get_Station_By_Name(stations, station_name));

			schedules.emplace_back(std::move(tmp_station_reference), std::move(timetable), std::move(schedule.first), line_parse_data.first+schedule.second.filename().string());
		}
		scheduled_lines.emplace_back(std::move(schedules), std::move(line_parse_data.first));
	}
	return std::make_pair(std::move(stations), std::move(scheduled_lines));
}