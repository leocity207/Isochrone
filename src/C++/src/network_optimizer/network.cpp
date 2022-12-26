#include "includes/network_optimizer/network.h"

//ressource
#include "includes/resource/resource_getter.h"
#include "includes/resource/csv_schedule_reader.h"
#include "includes/resource/csv_station_reader.h"

//network
#include "includes/network_optimizer/schedule.h"
#include "includes/network_optimizer/day_info.h"

//utils
#include "includes/utils/exception_def.h"


Network::Network(const std::filesystem::path& resource_path)
{
	Resource_Getter	getter(resource_path);

	m_station_list =  CSV_Station_Reader::Read_Station_File(resource_path/getter.Get_Station_File());

	for(const auto& line_parse_data : getter.Get_Line_Files())
	{
		std::vector<Schedule> schedules;
		for(const auto& schedule : line_parse_data.second)
		{
			DayTemplate temp(schedule.filename().string());
			auto [station_list, timetable] = CSV_Schedule_Reader::Read_Schedule_File(schedule);
			Schedule(std::move(this->Get_Station_Reference(station_list)),std::move(timetable),std::move(temp));
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

const std::vector<Line>& Network::Get_Lines() const noexcept
{
	return m_line_list;
}
const std::vector<Station>& Network::Get_Station() const noexcept
{
	return m_station_list;
}