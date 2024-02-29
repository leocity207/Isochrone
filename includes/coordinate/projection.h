#ifndef COORDINATE_PROJECTION_H
#define COORDINATE_PROJECTION_H

// Utils
#include "includes/utils/ctor.h"

// Coordinate
#include "sphere.h"

namespace Coordinate
{
	using Planare_double = Base<double>;
	class Projection
	{
		////////
		/// CTOR
	public:
		Projection(Spherical&& mean_coordiante) noexcept;

		////////////
		/// METHODS
	public:
		virtual Planare_double Project(const Spherical& coordinate) = 0;

		//////////////
		/// ATTRIBUTES
	protected:
		Spherical m_mean_coordinate;
	};

	class Equirectangular : public Projection
	{
		////////////
		/// METHDODS
	public:
		Planare_double Project(const Spherical& coordinate) override;
	};

	class Azimuthal_Equidistant : public Projection
	{
		////////////
		/// METHDODS
	public:
		Planare_double Project(const Spherical& coordinate) override;
	};
}

#endif