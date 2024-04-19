#ifndef REACH_ALGORITHM_SIMPLE_H
#define REACH_ALGORITHM_SIMPLE_H


// Reach algorithm
#include "algorithm.h"


namespace Reach_Algorithm
{
	//TEST 0.713ms VIENNE 1440
	class Simple : public Algorithm
	{

	//#####
	// CTOR
	public:
		DEFAULT_DEFAULT_CTOR(Simple)
		DELETE_COPY(Simple)
		DELETE_MOVE(Simple)


	//########
	// METHODS
	public:
		std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& algorithm_context) override;
	};
	
}; //Reach Algorithm


#endif //REACH_ALGORITHM_SIMPLE_H