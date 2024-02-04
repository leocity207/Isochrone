#ifndef REACH_ALGORITHM_ALGORITHM_H
#ifndef REACH_ALGORITHM_ALGORITHM_H


/// Utils
#include "includes/utils/ctor.h"

/// Context
#include "includes/context/station.h"

namespace Context
{
	class Reach_Algorithm;
}

namespace Reach_Algorithm
{
	class Algorithm
	{
		////////
		/// CTOR
	public:
		DELETE_COPY(Algorithm);
		DELETE_DEFAULT(Algorithm);
		DELETE_MOVE(Algorithm);

		Algorithm(e) noexcept;

		/////////////
		/// METTHODS
	public:
		virtual std::vector<Context::Station> Optimize(const Context::Reach_Algorithm& day_typ) = 0;


	};
}

#endif // !REACH_ALGORITHM_ALGORITHM_H
