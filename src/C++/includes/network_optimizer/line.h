#ifndef LINE_H
#define LINE_H

#include <vector>

#include "station.h"

class Line
{
    private:
        std::vector<Station&> m_station_list;
        std::string m_name;
        int m_ID;
        Schedule m_schedule;
        static int s_count;
    public:
        Line() noexcept;
        Line(std::vector<Station&> Schedule);
        
        const Planar_Coordinate& GetCoordinate() const ;
        const float Get_Distance_To(const Station& station) const;
        const float Get_Distance_To(const Planar_Coordinate& station) const;
};

#endif //LINE_H