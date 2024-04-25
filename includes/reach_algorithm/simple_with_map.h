#ifndef REACH_ALGORITHM_SIMPLE_WITH_MAP_H
#define REACH_ALGORITHM_SIMPLE_WITH_MAP_H


// Reach algorithm
#include "algorithm.h"


namespace Reach_Algorithm
{
	/////////////////////////////////////////////////////
	/// @brief Simple algorithm with parallele execution
	/// @warning 0.518ms VIENNE 1440
	/// @note  default_constructible
	///        not_copy_constructible
	///        not_copy_assignable
	///        not_move_constructible
	///        not_move_asignable
	class Simple_With_Map : public Algorithm
	{

	//######
	// CTOR
	public:
		DEFAULT_DEFAULT_CTOR(Simple_With_Map)
		DELETE_COPY(Simple_With_Map)
		DELETE_MOVE(Simple_With_Map)


	//########
	// METHODS
	public:
		std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& algorithm_context) override;
	};
	
}; //Reach Algorithm


#endif //REACH_ALGORITHM_SIMPLE_WITH_MAP_H