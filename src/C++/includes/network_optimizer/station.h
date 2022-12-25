#ifndef STATION_H
#define STATION_H

#include <string>
#include <functional>
#include "includes/utils/coordinate_2d.h"


class Station
{
    private:
        const Sphere_Coordinate m_coordinate;
        const std::string m_name;
        const int m_id;
        static int s_count;

    public:
        Station() = delete;
        Station(Sphere_Coordinate&& coordinate, std::string&& name) noexcept;

        Station(const Station&) = delete;
        explicit Station(Station&&) noexcept;
        
        
        /////////////////////////////////
        /// @brief give back the name of the station
        /// @return the name of the station
        const std::string& Get_Name() const noexcept;

        /////////////////////////
        /// @brief give back the coordinate of the station
        /// @return the coordinate of the station
        const Sphere_Coordinate& GetCoordinate() const noexcept;

        //////////////////////////////////
        /// @brief give back the distance from the parameter station to this station
        /// @param station  the station to compute the distance too
        /// @return the distance to the two station in meter
        const double Get_Distance_To(const Station& station) const noexcept;

        //////////////////////////////////////
        /// @brief give back the distance from this station to the given coordinate
        /// @param station the coordinate you want to compute the distance too
        /// @return 
        const double Get_Distance_To(const Sphere_Coordinate& coordinate) const noexcept;


        bool operator==(const Station& other_station) const noexcept;
};

typedef std::reference_wrapper<const Station> Station_CRef;

#endif //STATION_H