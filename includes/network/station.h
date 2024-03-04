#ifndef NETWORK_STATION_H
#define NETWORK_STATION_H

// STL
#include <string>
#include <vector>

// Coordinate
#include "includes/coordinate/sphere.h"

// Utils
#include "includes/utils/ctor.h"


namespace Network
{
	class Station
	{
	/////////
	/// CTOR
	public:
		DELETE_DEFAULT_CTOR(Station)
		DELETE_COPY(Station)
		DEFAULT_MOVE(Station)
		Station(Coordinate::Spherical&& coordinate, std::string&& name) noexcept;

	///////////
	/// METHODS
	public:
		////////////////////////////////////////////////////////////////////////////
		/// @brief give back the distance from the parameter station to this station
		/// @param station  the station to compute the distance too
		/// @return the distance to the two station in meter
		const double Get_Distance_To(const Station& station) const noexcept;

		///////////////////////////////////////////////////////////////////////////
		/// @brief give back the distance from this station to the given coordinate
		/// @param station the coordinate you want to compute the distance too
		/// @return 
		const double Get_Distance_To(const Coordinate::Spherical& coordinate) const noexcept;

		/////////////////////////////////////////////////////////////
		/// @brief comparison operator compare station using their ID
		bool operator==(const Station& other_station) const noexcept;
		bool operator<(const Station& other_station) const noexcept;

		//////////
		/// getter
		const std::string& Get_Name() const noexcept;
		const Coordinate::Spherical& GetCoordinate() const noexcept;

	//////////////////
	/// STATIC METHODS
	public:
		static const Station& Get_Station_By_Name(const std::vector<Station>& station_list, const std::string& name);

	//////////////
	/// ATTRIBUTES
	private:
		Coordinate::Spherical m_coordinate;
		std::string m_name;
		int m_id;
		static int s_count;
	};

	using Station_CRef = std::reference_wrapper<const Station> ;

}// Network

#endif //NETWORK_STATION_H