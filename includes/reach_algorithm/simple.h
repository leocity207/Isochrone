#ifndef REACH_ALGORITHM_SIMPLE_H
#define REACH_ALGORITHM_SIMPLE_H


// Reach algorithm
#include "algorithm.h"


namespace Reach_Algorithm
{

	/////////////////////////////////////////////////////
	/// @brief Simple algorithm with parallele execution
	/// @warning 0.713ms VIENNE 1440
	/// @note  default_constructible
	///        not_copy_constructible
	///        not_copy_assignable
	///        not_move_constructible
	///        not_move_asignable
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