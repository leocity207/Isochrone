#ifndef REACH_ALGORITHM_SIMPLE_H
#define REACH_ALGORITHM_SIMPLE_H

//TEST 0.713ms
//reach_algorithm
#include "algorithm.h"

namespace Reach_Algorithm
{
	class Simple : public Algorithm
	{

	////////
	/// CTOR
	public:
		DEFAULT_DEFAULT(Simple)
		DELETE_COPY(Simple)
		DELETE_MOVE(Simple)


	//////////
	/// METHODS
	public:
		std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& algorithm_context) override;
	};
}; //Reach_Algorithm


#endif //REACH_ALGORITHM_SIMPLE_H