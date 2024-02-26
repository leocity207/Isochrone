#ifndef REACH_ALGORITHM_SIMPLE_PAR_H
#define REACH_ALGORITHM_SIMPLE_PAR_H


// Reach algorithm
#include "algorithm.h"

namespace Reach_Algorithm
{
	
	//TEST 1.308ms VIENNE 1440
	class Simple_Par : public Algorithm
	{

	////////
	/// CTOR
	public:
		DEFAULT_DEFAULT(Simple_Par)
		DELETE_COPY(Simple_Par)
		DELETE_MOVE(Simple_Par)


	//////////
	/// METHODS
	public:
		std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& algorithm_context) override;
	};
	
}; //Reach Algorithm


#endif //REACH_ALGORITHM_SIMPLE_PAR_H