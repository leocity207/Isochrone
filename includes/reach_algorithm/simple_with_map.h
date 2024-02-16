#ifndef REACH_ALGORITHM_SIMPLE_WITH_MAP_H
#define REACH_ALGORITHM_SIMPLE_WITH_MAP_H

//TEST 0.518ms
//reach_algorithm
#include "algorithm.h"

namespace Reach_Algorithm
{
	class Simple_With_Map : public Algorithm
	{

	////////
	/// CTOR
	public:
		DEFAULT_DEFAULT(Simple_With_Map)
		DELETE_COPY(Simple_With_Map)
		DELETE_MOVE(Simple_With_Map)


	//////////
	/// METHODS
	public:
		std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& algorithm_context) override;
	};
}; //Reach_Algorithm


#endif //REACH_ALGORITHM_SIMPLE_WITH_MAP_H