#include "includes/reach_algorithm/optimized.h"
#include "includes/context/reach_algorithm.h"

#include <algorithm>
#include <ranges>
#include <cassert>
#include <map>
#include <execution>

std::vector<Context::Station> Reach_Algorithm::Optimized::Optimize(const Context::Reach_Algorithm& algorithm_context)
{
	std::list<Context::Station> station_list;
	std::vector<Context::Station> final_optimized;
	const std::list<Context::Station>::iterator* best_item = nullptr;
    std::map < Network::Station_CRef, std::reference_wrapper<Context::Station>, std::less<const Network::Station>> smap;

	for (const Network::Station& station : algorithm_context.Get_Network().Get_Station())
	{
        station_list.emplace_back(station, algorithm_context);
        station_list.back().Set_Pos(--station_list.end());
        smap.insert({ station, station_list.back() });
        if (!best_item || (*best_item)->Get_Reaching_Time() > station_list.back().Get_Reaching_Time())
            best_item = &(station_list.back().Get_Pos());
	}


 	/////////////////////////
    // run throug all station
    // O(S)
	for(size_t i = station_list.size()-1;i--;)
	{
		//order list and pop the best element;
        final_optimized.emplace_back(std::move(**best_item));
        station_list.erase(*best_item);
        best_item = nullptr;
		Context::Station& current_station = final_optimized.back();

		///////////////////////////////////////////////////////////////////
        //get list of lines passing at the choosen station
        // O(L)
        // could be improved by cahcing the passing line inside the station
		auto line_list = std::views::filter(algorithm_context.Get_Network().Get_Scheduled_Lines(), [&](const Network::Scheduled_Line& line) {
			return line.Contain(current_station.Get(), algorithm_context.Get_Day_Type());
		});

        //////////////////////////////////////////////////////////////////////
        // Check for reaching station by base speed
        // passage to this function is mandatory to update the best time value
        // Sequential is O(S)
        // Parallele is O(1)
        std::for_each(std::execution::seq, station_list.begin(), station_list.end(), [&](Context::Station& alg_station) {
            std::chrono::seconds default_time((int)std::round(current_station.Get().Get_Distance_To(alg_station.Get()) / algorithm_context.Get_Speed()));
            DayTime time = current_station.Get_Reaching_Time() + default_time;
            alg_station.Try_Set_New_Best_Time_Base(time);
            if(!best_item || alg_station.Get_Reaching_Time() < (*best_item)->Get_Reaching_Time())
                best_item = &(alg_station.Get_Pos());
        });

		//////////////////////////////////////////////////////////////////
        /// For all lines passing by the station
        /// At worst O(L) but more like the mean station passing by a line
        /// Paralelisable if each line don't meet
		std::for_each(std::execution::seq,line_list.begin(), line_list.end(), [&](const Network::Scheduled_Line& line) {

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// Get the right schedules for that day (could be cached)
            /// Complexcity is equivalent to the number of schedule wich is constant around at most 8 for some station
			auto schedule_list = line.Get_Schedules(algorithm_context.Get_Day_Type());
			/////////////////////////////////////////////////////////////////////////////////////////////
            /// Constant for the line and parralelisable for a specific line the size should always be 2 
			std::for_each(std::execution::seq,schedule_list.begin(), schedule_list.end(), [&](const Network::Schedule& schedule) {
				//////////////////////////////////////////////////////////////////////
                ///go for all station inside the line (this could be improved because )
				std::for_each(std::execution::seq,schedule.From_Station(current_station.Get()), schedule.Get_Station_List().cend(), [&](const Network::Station_CRef& station) {
					//no need to compute distance from the two same station
					std::optional<DayTime> value = schedule.Get_Closest_Time_To_Station(current_station.Get(), station.get(), current_station.Get_Reaching_Time());
                    Context::Station& end_alg_station = smap.at(station).get();
                    //auto pose = std::find_if(station_list.begin(), station_list.end(), [&](const Algorithm_Station& alg_station) {return alg_station.Get() == station; });
                    if ((end_alg_station.Try_Set_New_Best_Time_Transport(value) && value<(*best_item)->Get_Reaching_Time()))
                         best_item = &(end_alg_station.Get_Pos());
				});
			});
		});

	}

	//dont forget the last element
	final_optimized.emplace_back(std::move(station_list.back()));
	return final_optimized;
}