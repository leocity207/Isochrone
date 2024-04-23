#ifndef CONTEXT_REACHED_STATION_H
#define CONTEXT_REACHED_STATION_H

// STL
#include <optional>
#include <mutex>
#include <list>

// Utils
#include "includes/utils/ctor.h"
#include "includes/utils/daytime.h"

// Network
#include "includes/network/station.h"


namespace Context
{
	
	class Reach_Algorithm;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Class describing a station for the algorithm
	///        It hold the best time we arrive at this station
	///        It also hold extra information about how we reach the station
	/// @note not_default_constructible
	///       not_copy_constructible
	///       not_copy_assignable
	///       move_constructible
	///       move_asignable
	class Station
	{
	
	//#####
	// CTOR
	public:
		DELETE_DEFAULT_CTOR(Station);
		DELETE_COPY(Station);
		Station(Station&&) noexcept;
		Station& operator=(Station&&) noexcept;

		////////////////////////////////////////////////////
		/// @brief Explicit constructor by move construction
		Station(const Network::Station& station_to_link,const Reach_Algorithm& reach_algorithm_context) noexcept;

	//########
	// METHODS
	public:
		////////////////////////////////////////////////////////////////////////////
		/// @brief Give back the time you need to get from this station to the start
		/// @return the daytime at which we reach the station
		const DayTime& Get_Reaching_Time() const noexcept;

		///////////////////////////////////////////////////////////////////////////
		/// @brief try and see if the new daytime is better than the registered one
		/// @param new_value the new daytime value to reach the station where we want to see if better
		bool Try_Set_New_Best_Time_Base(DayTime& new_value);
		bool Try_Set_New_Best_Time_Base(std::optional<DayTime>& new_value);
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief try and see if the new daytime is better than the registered one also set that the station has been reached by transport
		/// @param new_value the new daytime value to reach the station where we want to see if better
		bool Try_Set_New_Best_Time_Transport(DayTime& new_value);
		bool Try_Set_New_Best_Time_Transport(std::optional<DayTime>& new_value);
		

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief try and see if the new daytime is better than the registered one this function is protected by mutex
		/// @param new_value the new daytime value to reach the station where we want to see if better
		bool Try_Set_New_Best_Time_Transport_Lock(std::optional<DayTime>& new_value);

		/////////////////////////////////////
		/// @brief Way to get the containing station
		const Network::Station& Get() const noexcept;

		///////////////////////
		/// @brief Comparaison
		bool operator<(const Context::Station &other_station) const noexcept;
		
		/////////////////////////////////////////////////////////////////////////////////////
		/// @brief Tells wether or not this station has been reach by transport and no walk
		bool Has_Been_Reached_By_Transport() const noexcept;
		
		/////////////////////////////////////////////////////
		/// @brief Tells wether or not we used trasport to reach this station
		bool Has_Been_Reached_Once_By_Transport() const noexcept;

		//////////////////////////////////////////////////////////////////////////
		/// @brief Setter to set the iterator of the referenced station
		void Set_Pos(std::list<Station>::iterator& pos);
		//////////////////////////////////////////////////////////////////////////
		/// @brief getter to the iterator of the referenced station
		const std::list<Station>::iterator& Get_Pos() const;

	//###############
	// STATIC METHODS
	public:
		/////////////////////////////////////////////////////
		/// @brief          Give back the station from a list 
		/// @param stations List where to find the station
		/// @param name     Name of the station we are looking for
		/// @throw			"STATION_NOT_IN_LIST" if the station is not in list STATION_NOT_IN_LIST
		static const Station& Get_Station_By_Name(const std::vector<Station>& stations, const std::string& name);


	//###########
	// ATTRIBUTES
	private:
		DayTime m_best_time;
		DayTime m_basic_time;
		bool m_reach_by_transport = false;
		bool m_reach_by_transport_once = false;
		std::reference_wrapper<const Network::Station> m_ref_station;
		std::optional<std::list<Context::Station>::iterator> m_pos = std::nullopt;
		std::mutex m_mutex = std::mutex();
	};
	
	using Station_CRef = std::reference_wrapper<Station>;
	
}// Network

#endif // !CONTEXT_REACHED_STATION_H
