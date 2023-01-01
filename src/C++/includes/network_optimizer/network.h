#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <filesystem>

#include "includes/network_optimizer/station.h"
#include "includes/network_optimizer/line.h"


class Network
{
public:
    Network() = delete;
    Network(const std::filesystem::path& resource_path);
    const std::vector<Line>& Get_Lines() const noexcept {return m_line_list;};
    const std::vector<Station>& Get_Station() const noexcept {return m_station_list;};
    
    std::vector<Station_CRef> Get_Station_Reference(std::vector<std::string> station_name_list);
    std::vector<Line_CRef> Get_Passing_Lines(const Station& station, const Day& day);
    
private:
    std::vector<Station> m_station_list;
    std::vector<Line> m_line_list;
};


#endif //NETWORK_H