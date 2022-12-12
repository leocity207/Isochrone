#ifndef STATION_H
#define STATION_H

#include <string>
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
        Station(Sphere_Coordinate&& coordinate, std::string&& name) noexcept;
        
        const std::string& GetName() noexcept const;
        const Sphere_Coordinate& GetCoordinate() noexcept const;
        const float Get_Distance_To(const Station& station) const;
        const float Get_Distance_To(const Sphere_Coordinate& station) const;
        bool operator==(const Station&) const;
};

#endif //STATION_H