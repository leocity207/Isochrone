#ifndef NETWORK_H
#define NETWORK_H

#include <vector>

class Station;
class Line;
class Network
{
    std::vector<Station> m_station_list;
    std::vector<Line> m_line_list;
}


#endif //NETWORK_H