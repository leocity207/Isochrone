#ifndef REACH_ALGORITHM_ALGORITHM_H
#define REACH_ALGORITHM_ALGORITHM_H


/// Utils
#include "includes/utils/ctor.h"

/// Context
#include "includes/context/station.h"

#include <map>

namespace Context
{
	class Reach_Algorithm;
}

namespace Reach_Algorithm
{
	class Algorithm
	{
	////////
	/// CTOR
	public:
		DEFAULT_DEFAULT(Algorithm)
		DELETE_COPY(Algorithm);
		DELETE_MOVE(Algorithm);

	/////////////
	/// METTHODS
	public:
		virtual std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& day_typ) = 0;

	//////////////////
	/// STATIC METHODS
	protected:
		static void Place_Min_Reaching_Time_At_End(std::vector<Context::Station>& list);
		static void Place_Min_Reaching_Time_At_End(std::vector<Context::Station>& list, std::map<Network::Station_CRef, Context::Station_CRef, std::less<const Network::Station>>& map);
		static Context::Station& Pop_Best_Reached_Station(std::vector<Context::Station>& remaining_list, std::vector<Context::Station>& optimized_list);
		static Context::Station& Pop_Best_Reached_Station(std::vector<Context::Station>& remaining_list, std::vector<Context::Station>& optimized_list, std::map<Network::Station_CRef, Context::Station_CRef, std::less<const Network::Station>>& map);
		static void Test_Walking_Time_From_Station(Context::Station& starting_station, std::vector<Context::Station>& remaining_stations, double walking_speed);
		static void Test_Walking_Time_From_Station_Par(Context::Station& starting_station, std::vector<Context::Station>& remaining_stations, double walking_speed);
	};
};

#endif // REACH_ALGORITHM_ALGORITHM_H
