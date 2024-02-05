#ifndef REACH_ALGORITHM_OPTIMIZED_H
#define REACH_ALGORITHM_OPTIMIZED_H


//reach_algorithm
#include "algorithm.h"

namespace Reach_Algorithm
{
	class Optimized : public Algorithm
	{

	////////
	/// CTOR
	public:
		DEFAULT_DEFAULT(Optimized)
		DELETE_COPY(Optimized)
		DELETE_MOVE(Optimized)


	//////////
	/// METHODS
	public:
		std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& algorithm_context) override;
	};
}; //Reach_Algorithm


#endif //REACH_ALGORITHM_OPTIMIZED_H