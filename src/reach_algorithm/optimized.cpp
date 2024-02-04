#include "includes/reach_algorithm/optimized.h"
#include "includes/context/reach_algorithm.h"

#include <algorithm>
#include <ranges>
#include <cassert>
#include <map>


Reach_Algorithm::Optimized::Optimized(const Context::Reach_Algorithm& day_type) noexcept :
	Reach_Algorithm::Algorithm(day_type)
{

}

std::vector<Context::Station> Reach_Algorithm::Optimized::Optimize(const Context::Reach_Algorithm& algorithm_context)
{
	std::vector<Context::Station> station_list;
	std::vector<Context::Station> final_optimized;
	station_list.reserve(algorithm_context.Get_Network().Get_Station().size());

	for (const Network::Station& station : algorithm_context.Get_Network().Get_Station())
		station_list.emplace_back(&station, this);



	for(size_t i = station_list.size()-1;i--;)
	{
		//order list and pop the best element;
		std::sort(station_list.begin(), station_list.end());
		std::reverse(station_list.begin(), station_list.end());
		final_optimized.emplace_back(std::move(station_list.back()));
		station_list.pop_back();
		Context::Station& current_station = final_optimized.back();

		//get list of lines passing at the choosen station
		auto line_list = std::views::filter(algorithm_context.Get_Network().Get_Scheduled_Lines(), [&](const Network::Scheduled_Line& line) {
			return line.Contain(current_station.Get(), algorithm_context.Get_Day_Type());
		});

		for (Context::Station& alg_station : station_list)
		{
			std::chrono::seconds default_time((int)std::round(current_station.Get().Get_Distance_To(alg_station.Get())/ algorithm_context.Get_Speed()));
			DayTime time = current_station.Get_Best_Time_Start_To_Station() + default_time;
			alg_station.Try_Set_New_Best_Time(time);
		}

		//for all lines passing by the station
		std::for_each(line_list.begin(), line_list.end(), [&](const Network::Line& line) { 
			auto schedule_list = line.Get_Schedules(algorithm_context.Get_Day_Type());
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