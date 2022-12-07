#ifndef STATION_H
#define STATION_H

#include <string>
#include "includes/utils/coordinate_2d.h"


class Station
{
    private:
        Planar_Coordinate m_relative_coordinate;
        std::string m_name;
        static int s_count;
    public:
        Station() noexcept;
        Station(Planar_Coordinate coordiante);
        
        const Planar_Coordinate& GetCoordinate() const ;
        const float Get_Distance_To(const Station& station) const;
        const float Get_Distance_To(const Planar_Coordinate& station) const;
};

#endif //STATION_H