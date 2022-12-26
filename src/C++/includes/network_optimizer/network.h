#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <filesystem>

class Station;
class Line;
class Network
{
public:
    Network() = delete;
    Network(const std::filesystem::path& resource_path);
    const std::vector<Line>& Get_Lines() const noexcept;
    const std::vector<Station>& Get_Station() const noexcept;
    std::vector<Station_CRef> Get_Station_Reference(std::vector<std::string> station_name_list);
private:
    std::vector<Station> m_station_list;
    std::vector<Line> m_line_list;
}


#endif //NETWORK_H