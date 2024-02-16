#include "includes/reach_algorithm/algorithm.h"

#include <algorithm>
#include <execution>

void Reach_Algorithm::Algorithm::Place_Min_Reaching_Time_At_End(std::vector<Context::Station>& list)
{
	auto min_element_it = std::min_element(list.begin(), list.end(), [](Context::Station& a, Context::Station& b) {return a.Get_Reaching_Time() < b.Get_Reaching_Time(); });
	std::iter_swap(min_element_it, --list.end());
}

void Reach_Algorithm::Algorithm::Place_Min_Reaching_Time_At_End(std::vector<Context::Station>& list, std::map<Network::Station_CRef, Context::Station_CRef, std::less<const Network::Station>>& map)
{
	auto min_element_it = std::min_element(list.begin(), list.end(), [](Context::Station& a, Context::Station& b) {return a.Get_Reaching_Time() < b.Get_Reaching_Time(); });
	std::iter_swap(min_element_it, --list.end());
	std::swap(map.at(min_element_it->Get()), map.at(list.back().Get()));
}

void Reach_Algorithm::Algorithm::Test_Walking_Time_From_Station(Context::Station& starting_station, std::vector<Context::Station>& remaining_stations, double walking_speed)
{
	std::for_each(std::execution::unseq, remaining_stations.begin(), remaining_stations.end(), [&](Context::Station& remaining_station) {
		std::chrono::seconds inter_station_walking_time((int)std::round(starting_station.Get().Get_Distance_To(remaining_station.Get()) / walking_speed));
		DayTime time = starting_station.Get_Reaching_Time() + inter_station_walking_time;
		remaining_station.Try_Set_New_Best_Time_Base(time);
	});
}

void Reach_Algorithm::Algorithm::Test_Walking_Time_From_Station_Par(Context::Station& starting_station, std::vector<Context::Station>& remaining_stations, double walking_speed)
{
	std::for_each(std::execution::par_unseq, remaining_stations.begin(), remaining_stations.end(),[&](Context::Station& remaining_station){
		std::chrono::seconds inter_station_walking_time((int)std::round(starting_station.Get().Get_Distance_To(remaining_station.Get()) / walking_speed));
		DayTime time = starting_station.Get_Reaching_Time() + inter_station_walking_time;
		remaining_station.Try_Set_New_Best_Time_Base(time);
	});
}


Context::Station& Reach_Algorithm::Algorithm::Pop_Best_Reached_Station(std::vector<Context::Station>& remaining_list, std::vector<Context::Station>& optimized_list)
{
	optimized_list.emplace_back(std::move(remaining_list.back()));
	remaining_list.pop_back();
	return optimized_list.back();
}

Context::Station& Reach_Algorithm::Algorithm::Pop_Best_Reached_Station(std::vector<Context::Station>& remaining_list, std::vector<Context::Station>& optimized_list, std::map<Network::Station_CRef, Context::Station_CRef, std::less<const Network::Station>>& map)
{
map.erase(remaining_list.back().Get());
optimized_list.emplace_back(std::move(remaining_list.back()));
remaining_list.pop_back();
return optimized_list.back();
}
