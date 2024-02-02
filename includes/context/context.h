#ifndef CONTEXT_H
#define CONTEXT_H

#include "includes/utils/coordinate_2d.h"

#include "includes/network/line.h"
#include "includes/network/station.h"

namespace Context
{
	class Network
	{
	private:
		std::vector<Network::Lines> m_lines;
		std::vector<Network::Station> m_stations;
	};

	class Solver
	{
	private:
		Reach_Algorithm m_algorithm;
		Sphere_Coordinate m_starting_coordinate;
		double m_walking_speed;
		const Network& m_network;
	};
}

#endif // CONTEXT_H