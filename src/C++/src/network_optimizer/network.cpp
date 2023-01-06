#include "includes/network_optimizer/network.h"

//ressource
#include "includes/resource/resource_getter.h"
#include "includes/resource/csv_schedule_reader.h"
#include "includes/resource/csv_station_reader.h"

//network
#include "includes/network_optimizer/day_info.h"


//utils
#include "includes/utils/exception_def.h"


Network::Network(const std::filesystem::path& resource_path) : m_line_list(), m_station_list()
{
	Resource_Getter	getter(resource_path);

	m_station_list =  std::move(CSV_Station_Reader::Read_Station_File(resource_path.parent_path()/getter.Get_Station_File()));

	for(auto& line_parse_data : getter.Get_Line_Files())
	{
		std::vector<Schedule> schedules;
		for(auto& schedule : line_parse_data.second)
		{
			auto [station_list, timetable] = CSV_Schedule_Reader::Read_Schedule_File(resource_path.parent_path()/schedule.second);
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