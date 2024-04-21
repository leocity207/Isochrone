#ifndef NETWORK_STATION_H
#define NETWORK_STATION_H

// STL
#include <string>
#include <vector>

// Coordinate
#include "includes/coordinate/sphere.h"

// Utils
#include "includes/utils/ctor.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Network namesapce represent object inside a network it is mainly used for descriptive object 
namespace Network
{
	///////////////////////////////////////////////////////////////////////////////
	/// @brief Represent a station inside a network
	/// @note not_default_constructible
	///       not_copy_constructible
	///       not_copy_assignable
	///       move_constructible
	///       move_asignable
	class Station
	{
	//#####
	// CTOR
	public:
		DELETE_DEFAULT_CTOR(Station)
		DELETE_COPY(Station)
		DEFAULT_MOVE(Station)

		////////////////////////////////////////////////////
		/// @brief Explicit constructor by move construction
		Station(Coordinate::Spherical&& coordinate, std::string&& name) noexcept;

	//########
	// METHODS
	public:
		////////////////////////////////////////////////////////////////////////////
		/// @brief         Give back the distance from the parameter station to this station
		/// @param station The station to compute the distance too
		/// @return        The distance to the two station in meter
		const double Get_Distance_To(const Station& station) const noexcept;

		///////////////////////////////////////////////////////////////////////////
		/// @brief         Give back the distance from this station to the given coordinate
		/// @param station The coordinate you want to compute the distance too
		/// @return        The distance to the two station in meter
		const double Get_Distance_To(const Coordinate::Spherical& coordinate) const noexcept;

		/////////////////////////////////////////////////////////////
		/// @brief Comparison operator compare station using their ID
		bool operator==(const Station& other_station) const noexcept;
		bool operator<(const Station& other_station) const noexcept;

		////////////////
		///@brief Getter
		const std::string& Get_Name() const noexcept;

		////////////////
		///@brief Getter
		const Coordinate::Spherical& GetCoordinate() const noexcept;

	//###############
	// STATIC METHODS
	public:

		/////////////////////////////////////////////////////////////
		/// @brief              Find a station inside a station list
		/// @param station_list The pool of station to look into
		/// @param name         The name of the station we are looking for
		/// @return             The Station object referencing the name of the station
		/// @throw              "STATION_NOT_IN_LIST" if the station is not found inside the list
		static const Station& Get_Station_By_Name(const std::vector<Station>& station_list, const std::string& name);

	//###########
	// ATTRIBUTES
	private:
		Coordinate::Spherical m_coordinate;
		std::string m_name;
		int m_id;
		static int s_count;
	};

	using Station_CRef = std::reference_wrapper<const Station> ;

}// Network

#endif //NETWORK_STATION_H