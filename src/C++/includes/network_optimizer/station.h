#ifndef STATION_H
#define STATION_H

#include <string>
#include <functional>
#include "includes/utils/coordinate_2d.h"

class Station
{
    private:
        Sphere_Coordinate m_coordinate;
        std::string m_name;
        int m_id;
        static int s_count;

    public:

        //delted function
        Station() = delete;
        Station(const Station&) = delete;
        Station& operator=(const Station&) = delete;

        Station(Sphere_Coordinate&& coordinate, std::string&& name) noexcept;
        Station(Station&&) noexcept = default;
        

        ////////////////////////////////////////////////////////////////////////////
        /// @brief give back the distance from the parameter station to this station
        /// @param station  the station to compute the distance too
        /// @return the distance to the two station in meter
        const double Get_Distance_To(const Station& station) const noexcept;

        ///////////////////////////////////////////////////////////////////////////
        /// @brief give back the distance from this station to the given coordinate
        /// @param station the coordinate you want to compute the distance too
        /// @return 
        const double Get_Distance_To(const Sphere_Coordinate& coordinate) const noexcept;

        /////////////////////////////////////////////////////////////
        /// @brief comparison operator compare station using their ID
        bool operator==(const Station& other_station) const noexcept{ return m_id == other_station.m_id;};
        bool operator!=(const Station& other_station) const noexcept{ return m_id != other_station.m_id;};
        bool operator<(const Station& other_station) const noexcept { return m_id < other_station.m_id;};

        //////////
        /// getter
        const std::string& Get_Name() const noexcept { return m_name; };
        const Sphere_Coordinate& GetCoordinate() const noexcept { return m_coordinate; };
};

typedef std::reference_wrapper<const Station> Station_CRef;

#endif //STATION_H