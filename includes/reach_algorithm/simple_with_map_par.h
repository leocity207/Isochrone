#ifndef REACH_ALGORITHM_SIMPLE_WITH_MAP_PAR_H
#define REACH_ALGORITHM_SIMPLE_WITH_MAP_PAR_H

//reach_algorithm
#include "algorithm.h"


namespace Reach_Algorithm
{
	//TEST 1.728ms VIENNE 1440
	class Simple_With_Map_Par : public Algorithm
	{

	////////
	/// CTOR
	public:
		DEFAULT_DEFAULT_CTOR(Simple_With_Map_Par)
		DELETE_COPY(Simple_With_Map_Par)
		DELETE_MOVE(Simple_With_Map_Par)

	//////////
	/// METHODS
	public:
		std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& algorithm_context) override;
	};
	
}; //Reach Algorithm


#endif //REACH_ALGORITHM_SIMPLE_WITH_MAP_PAR_H