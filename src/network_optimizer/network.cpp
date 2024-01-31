#include "includes/network_optimizer/network.h"

//ressource
#include "includes/resource/json/parser/resource_getter.h"
#include "includes/resource/csv/parser/timetable.h"
#include "includes/resource/csv/parser/station.h"
#include "includes/resource/csv/engine/file_parser.h"

//network
#include "includes/network_optimizer/day_info.h"


//utils
#include "includes/utils/exception_def.h"


Network::Network(const std::filesystem::path& resource_path) : m_line_list(), m_station_list()
{
	std::ifstream stream(resource_path);
	JSON::Parser::Resource_Getter getter(std::move(stream));

	CSV::Engine::File_Parser parser(resource_path.parent_path() / getter.Get_Station_File(), ';');
	m_station_list =  std::move(CSV::Parser::Station::Parse(parser));

	for(auto& line_parse_data : getter.Get_Line_Files())
	{
		std::vector<Timetable> schedules;
		for(auto& schedule : line_parse_data.second)
		{
			CSV::Engine::File_Parser timetable_parser(resource_path.parent_path() / schedule.second, ';');
			auto [station_list, timetable] = CSV::Parser::Timetable::Parse(timetable_parser);
			std::vector<Station_CRef> temp = this->Get_Station_Reference(station_list);

			schedules.emplace_back(std::move(temp),std::move(timetable),std::move(schedule.first));
		}
		m_line_list.emplace_back(std::move(schedules),std::move(line_parse_data.first));
	}
}

std::vector<Station_CRef> Network::Get_Station_Reference(std::vector<std::string> station_name_list)
{
	std::vector<Station_CRef> station_ref_list;
	for(const std::string& station_name : station_name_list)
	{
		auto is_same_name = [station_name](const Station& station){ return station.Get_Name() == station_name; };
		auto index = std::find_if(m_station_list.begin(),m_station_list.end(),is_same_name);
		if(index == m_station_list.end())
			THROW(Station_Not_In_Network)
		station_ref_list.emplace_back(*index);
	}
	return station_ref_list;
}

std::vector<Line_CRef> Network::Get_Passing_Lines(const Station& station,const Day& day)
{
	const std::reference_wrapper<const Station> station_ref(station);
	std::vector<Line_CRef> passing_lines;

	std::copy_if(m_line_list.begin(), m_line_list.end(), std::back_inserter(passing_lines), [day, station_ref](const Line& line) {return line.Contain(station_ref, day); });
	return passing_lines;
}

const std::vector<Line>& Network::Get_Lines() const noexcept 
{ 
	return m_line_list;
}

const std::vector<Station>& Network::Get_Station() const noexcept 
{
	return m_station_list;
}