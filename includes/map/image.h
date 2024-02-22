#ifndef MAP_IMAGE_H
#define MAP_IMAGE_H

// Utils
#include "includes/utils/rectangle.h"
#include "includes/utils/ctor.h"
#include "includes/utils/daytime.h"

namespace Context {
	class Reach_Algorithm;
	class Station;
}
namespace Network{ class Station; }
class Planar_Coordinate;


namespace Map
{
	class Image
	{
	////////
	/// CTOR
	public:
		DELETE_DEFAULT(Image);
		Image(const Context::Reach_Algorithm& context,const std::vector<Context::Station>& optimized_station, double resoltuion_per_pixel);

	///////////
	/// METHODS
	public:
		///////////////////////////////////////////
		/// @brief  : Compute the Isochrone map 
		/// @return : 2D image of the Isochrone map
		std::vector<std::vector<DayTime>> Compute_Time_Image();
	private:
		DayTime Compute_Time_To_Coordinate(const Context::Station&,const Planar_Coordinate&) const noexcept;
		DayTime Compute_Time_To_Coordinate(const Planar_Coordinate&, const Planar_Coordinate&) const noexcept;

	//////////////
	/// ATTRIBUTES
	private:
		Utils::Integer_Rectangle m_boundary;
		double m_meter_per_pixel;
		std::reference_wrapper<const std::vector<Context::Station>> m_stations;
		std::reference_wrapper<const Context::Reach_Algorithm> m_reach_context;
	};
}



#endif // MAP_IMAGE_H