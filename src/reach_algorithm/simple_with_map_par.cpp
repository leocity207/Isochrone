#include "includes/reach_algorithm/simple_with_map_par.h"
#include "includes/context/reach_algorithm.h"

// STL
#include <ranges>
#include <map>
#include <execution>


std::vector<Context::Station> Reach_Algorithm::Simple_With_Map_Par::Optimize(const Context::Reach_Algorithm& algorithm_context)
{
	std::vector<Context::Station> remaining_stations;
	std::vector<Context::Station> final_optimized;
	std::map<Network::Station_CRef, Context::Station_CRef, std::less<const Network::Station>> map;
	remaining_stations.reserve(algorithm_context.Get_Network().Get_Station().size());

	//////////////////////////////////////////////////////
	/// Construct the context station to the default value
	for (const Network::Station& station : algorithm_context.Get_Network().Get_Station())
	{
		remaining_stations.emplace_back(station, algorithm_context);
		map.emplace(Network::Station_CRef(station), Context::Station_CRef(remaining_stations.back()));
	}


	for (size_t i = remaining_stations.size() - 1; i--;)
	{
		//////////////////////////////////////////////
		/// Find the smallest element inside the list
		/// O(N)
		Place_Min_Reaching_Time_At_End(remaining_stations,map);
		Context::Station& current_station = Pop_Best_Reached_Station(remaining_stations,final_optimized, map);

		////////////////////////////////////////////////////////////////////
		/// Try to see if we can reach the remaining station faster by walk
		/// O(N) (O(1) if paralelized)
		Test_Walking_Time_From_Station(current_station, remaining_stations, algorithm_context.Get_Speed());

		///////////////////////////////////////////////////////
		// Get the list of line which pass at 'current_station'
		auto current_station_passing_lines = std::views::filter(algorithm_context.Get_Network().Get_Scheduled_Lines(), [&](const Network::Scheduled_Line& line) {
			return line.Contain(current_station.Get(), algorithm_context.Get_Day_Type());
		});

		//////////////////////////////////////////////////////////////////////
		/// For all lines passing by the station
		/// O(M) (O(1) if paralelize but need lock inside the context station)
		std::for_each(std::execution::par_unseq, current_station_passing_lines.begin(), current_station_passing_lines.end(), [&](const Network::Scheduled_Line& line) {
			auto schedule_list = line.Get_Schedules(algorithm_context.Get_Day_Type());

			///////////////////////////////////////////////////////
			/// For each schedule of that line
			/// O(2) (there should almost always be schedule for the A and R line)
			std::for_each(std::execution::par_unseq, schedule_list.begin(), schedule_list.end(), [&](const Network::Schedule& schedule) {

				//////////////////////////////////////////////////////////////////////
				/// For all station in the lines
				/// O(S) (O(1) if paralelize but need lock inside the context station)
				std::for_each(std::execution::par_unseq, schedule.Get_Station_List().begin(), schedule.Get_Station_List().end(), [&](const Network::Station_CRef& station) {
					///////////////////////////////////////////////////////
					// No need to compute distance from the two same station
					if (station.get() != current_station.Get()) {
						std::optional<DayTime> value = schedule.Get_Closest_Time_To_Station(current_station.Get(), station.get(), current_station.Get_Reaching_Time());
						if(map.count(station))
							map.at(station).get().Try_Set_New_Best_Time_Transport_Lock(value);
					}
				});
			});
		});
	}

	/////////////////////////////////
	/// Don't forget the last element
	final_optimized.emplace_back(std::move(remaining_stations.back()));
	return final_optimized;
}