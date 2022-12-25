#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <filesystem>

class Station;
class Line;
class Network
{
    Network() = delete;
    Network(const std::filesystem::path& resource_path);
    
    std::vector<Station> m_station_list;
    std::vector<Line> m_line_list;

    const std::vector<Line>& Get_Lines();
    const std::vector<Line>& Get_Station();

}


#endif //NETWORK_H