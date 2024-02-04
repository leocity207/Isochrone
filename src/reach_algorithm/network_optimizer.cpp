#include "includes/algorithm/network_optimizer.h"
#include "includes/algorithm/algorithm_station.h"

#include <algorithm>
#include <ranges>
#include <cassert>
#include <map>


Network_Optimizer::Network_Optimizer(const std::vector<Network::Station>& station,const std::vector<Network::Line>& lines,const Sphere_Coordinate& start_coordinate,const double default_speed,const DayTime& start_time,const Network::Day& day_type) noexcept : 
	m_stations(station),
	m_lines(lines),
	m_start_coordinate(start_coordinate),
	m_speed(default_speed), 
	m_start_time(start_time), 
	m_day_type(day_type)
{

}

const DayTime& Network_Optimizer::Get_Start_Time() const noexcept 
{
	return m_start_time;
}

const double Network_Optimizer::Get_Speed() const noexcept 
{
	return m_speed;
}

const Sphere_Coordinate& Network_Optimizer::Get_Start_Coordinate() const noexcept 
{
	return m_start_coordinate;
}


std::vector<Algorithm_Station> Network_Optimizer::Optimize()
{
	std::vector<Algorithm_Station> station_list;
	std::vector<Algorithm_Station> final_optimized;
	station_list.reserve(m_stations.size());

	for (const Network::Station& station : m_stations)
		station_list.emplace_back(&station, this);



	for(size_t i = station_list.size()-1;i--;)
	{
		//order list and pop the best element;
		std::sort(station_list.begin(), station_list.end());
		std::reverse(station_list.begin(), station_list.end());
		final_optimized.emplace_back(std::move(station_list.back()));
		station_list.pop_back();
		Algorithm_Station& current_station = final_optimized.back();

		//get list of lines passing at the choosen station
		auto line_list = std::views::filter(m_lines, [&](const Network::Line& line) {
			return line.Contain(current_station.Get(),m_day_type);
		});

		for (Algorithm_Station& alg_station : station_list)
		{
			std::chrono::seconds default_time((int)std::round(current_station.Get().Get_Distance_To(alg_station.Get())/m_speed));
			DayTime time = current_station.Get_Best_Time_Start_To_Station() + default_time;
			alg_station.Try_Set_New_Best_Time(time);
		}

		//for all lines passing by the station
		std::for_each(line_list.begin(), line_list.end(), [&](const Network::Line& line) { 
			auto schedule_list = line.Get_Schedules(m_day_type);
			//get the right schedules for that day
			std::for_each(schedule_list.begin(), schedule_list.end(), [&](const Network::Schedule& schedule) {
				//for all station in the lines
				std::for_each(schedule.Get_Station_List().begin(), schedule.Get_Station_List().end(), [&](const Network::Station_CRef& station) {
					//no need to compute distance from the two same station
					if (station.get() != current_station.Get()) {
						std::optional<DayTime> value = schedule.Get_Closest_Time_To_Station(current_station.Get(), station.get(), current_station.Get_Best_Time_Start_To_Station());
						auto pose = std::find_if(station_list.begin(), station_list.end(), [&](const Algorithm_Station& alg_station) {return alg_station.Get() == station; });
						if (pose != station_list.end())  
							pose->Try_Set_New_Best_Time(value);
					}
				});
			});
		});

	}

	//dont forget the last element
	final_optimized.emplace_back(std::move(station_list.back()));
	return final_optimized;
}