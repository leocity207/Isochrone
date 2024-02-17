#ifndef REACH_ALGORITHM_ALGORITHM_H
#define REACH_ALGORITHM_ALGORITHM_H

/// Utils
#include "includes/utils/ctor.h"

/// Context
#include "includes/context/station.h"

// STL
#include <map>

namespace Context { class Reach_Algorithm; }


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
		////////////////////////////////////////////////////////////////////////
		/// @brief         : This method optimize according to the given context 
		/// @param context : Context (and network context) to optimize
		/// @return        : List of context station that are ordered and reach optimized
		virtual std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& context) = 0;

	//////////////////
	/// STATIC METHODS
	protected:
		////////////////////////////////////////////////////////////////
		/// @brief      : Place the min element of list at the end of list 
		/// @param list : List where to find the min elemnt and to place it at the end via swap
		/// @param map  : Map to also update due to the swapping
		static void Place_Min_Reaching_Time_At_End(std::vector<Context::Station>& list);
		static void Place_Min_Reaching_Time_At_End(std::vector<Context::Station>& list, std::map<Network::Station_CRef, Context::Station_CRef, std::less<const Network::Station>>& map);
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief                : Remove the last element of remaining_list and place it inside the optimized list before returning a reference of it
		/// @param remaining_list : List where the last element will be popped
		/// @param optimized_list : List where the element will be added
		/// @param map            : Map to also update by removing the optimized element	
		/// @return               : The last optimized element
		static Context::Station& Pop_Best_Reached_Station(std::vector<Context::Station>& remaining_list, std::vector<Context::Station>& optimized_list);
		static Context::Station& Pop_Best_Reached_Station(std::vector<Context::Station>& remaining_list, std::vector<Context::Station>& optimized_list, std::map<Network::Station_CRef, Context::Station_CRef, std::less<const Network::Station>>& map);
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief                    : Try to see if starting from a station the walking time to the other station is better
		/// @param starting_station   : The station where we start our journey to other station
		/// @param remaining_stations : List of station where we can go
		/// @param walking_speed      : Speed at wich we walk between the stations	
		static void Test_Walking_Time_From_Station(Context::Station& starting_station, std::vector<Context::Station>& remaining_stations, double walking_speed);
		static void Test_Walking_Time_From_Station_Par(Context::Station& starting_station, std::vector<Context::Station>& remaining_stations, double walking_speed);
	};

}; // Reach_Algorithm


#endif // REACH_ALGORITHM_ALGORITHM_H
