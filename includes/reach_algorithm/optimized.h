#ifndef NETWORK_OPTIMIZER_H
#define NETWORK_OPTIMIZER_H


//reach_algorithm
#include "algorithm.h"

namespace Reach_Algorithm
{
	class Optimized : public Algorithm
	{

	////////
	/// CTOR
	public:
		DELETE_COPY(Optimized)
		DELETE_MOVE(Optimized)

	//////////
	/// METHODS
	public:
		std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& algorithm_context) override;
	};
}


#endif