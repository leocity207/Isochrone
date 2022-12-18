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
        Station() = delete;
        Station(const Station&) = delete;
        Station(Station&&) = delete;
        Station(Sphere_Coordinate&& coordinate, std::string&& name) noexcept;
        
        /////////////////////////////////
        /// @brief give back the name of the station
        /// @return the name of the station
        const std::string& GetName() noexcept const;

        /////////////////////////
        /// @brief give back the coordinate of the station
        /// @return the coordinate of the station
        const Sphere_Coordinate& GetCoordinate() noexcept const;

        //////////////////////////////////
        /// @brief give back the distance from the parameter station to this station
        /// @param station  the station to compute the distance too
        /// @return the distance to the two station in meter
        const double Get_Distance_To(const Station& station) const;

        //////////////////////////////////////
        /// @brief give back the distance from this station to the given coordinate
        /// @param station the coordinate you want to compute the distance too
        /// @return 
        const double Get_Distance_To(const Sphere_Coordinate& station) const;
        bool operator==(const Station&) const;
};

typedef std::reference_wrapper<const Station> Station_CRef;

#endif //STATION_H