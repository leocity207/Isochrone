#ifndef CONTEXT_REACH_ALGORITHM_H
#define CONTEXT_REACH_ALGORITHM_H

// Utils
#include "includes/utils/ctor.h"

// Network
#include "scheduled_network.h"

// Context
#include "includes/context/station.h"

namespace Reach_Algorithm { class Algorithm;};

namespace Context
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Context used to solve the Reach Algorithm
	///        To solve this problem ones need to know the speed, the starting point , and the starting point of the agent inside the network
	/// @note not_default_constructible
	///       not_copy_constructible
	///       not_copy_assignable
	///       move_constructible
	///       move_asignable
	class Reach_Algorithm
	{

	//#####
	// CTOR
	public:
		DELETE_DEFAULT_CTOR(Reach_Algorithm);
		DELETE_COPY(Reach_Algorithm);
		DEFAULT_MOVE(Reach_Algorithm);

		////////////////////////////////////////////////////
		/// @brief Explicit constructor by move construction
		Reach_Algorithm(const Scheduled_Network& network, DayTime&& start_time, double speed, Coordinate::Spherical&& starting_coordinate, Network::Day&& m_day_type) noexcept;

	//########
	// METHODS
	public:
		////////////////////////////////////////////////////////////////
		/// @brief getter for the network of the reach algorithm context
		const Scheduled_Network& Get_Network() const noexcept;
		//////////////////////////////////////////
		/// @brief getter for the starting time
		const DayTime& Get_Starting_Time() const noexcept;
		//////////////////////////////////////////
		/// @brief getter for the speed
		const double Get_Speed() const noexcept;
		//////////////////////////////////////////
		/// @brief getter for the starting coordinate
		const Coordinate::Spherical Get_Starting_Coordinate() const noexcept;
		//////////////////////////////////
		/// @brief getter for the Day_Type 
		const Network::Day& Get_Day_Type() const noexcept;

		///////////////////////////////////////////////////////////////////////////
		/// @brief           Optimize the scheduled network with the given optimizer algorithm
		/// @param algorithm The algorithm with wich we will optimize the network
		/// @return          List of context station optimized
		std::vector<Context::Station> Optimize(::Reach_Algorithm::Algorithm& algorithm) const;

	//###########
	// ATTRIBUTES
	private:
		std::reference_wrapper<const Scheduled_Network> m_network;
		DayTime m_start_time;
		double m_speed;
		Coordinate::Spherical m_start_coordinate;
		Network::Day m_day_type;
	};

};//Context

#endif // CONTEXT_REACH_ALGORITHM_H