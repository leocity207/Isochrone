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
	class Reach_Algorithm
	{

	//#####
	// CTOR
	public:
		DELETE_DEFAULT_CTOR(Reach_Algorithm);
		DELETE_COPY(Reach_Algorithm);
		DEFAULT_MOVE(Reach_Algorithm);

		Reach_Algorithm(const Scheduled_Network& network, DayTime&& start_time, double speed, Coordinate::Spherical&& starting_coordinate, Network::Day&& m_day_type) noexcept;

	//########
	// METHODS
	public:
		const Scheduled_Network& Get_Network() const noexcept;
		const DayTime& Get_Starting_Time() const noexcept;
		const double Get_Speed() const noexcept;
		const Coordinate::Spherical Get_Starting_Coordinate() const noexcept;
		const Network::Day& Get_Day_Type() const noexcept;

		///////////////////////////////////////////////////////////////////////////
		/// @brief otimize the scheduled network with the given optimizer algorithm
		/// @param algorithm the algorithm with wich we will optimize the network
		/// @return list of context station optimized
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