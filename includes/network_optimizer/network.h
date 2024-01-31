#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <filesystem>

#include "includes/network_optimizer/station.h"
#include "includes/network_optimizer/line.h"

///////////////////////////////////////
/// @brief class representing a network
class Network
{
public:
    //deleted
    Network() = delete;
    Network(const Network&) = delete;
    Network& operator=(const Network&) = delete;

    /////////////////////////////////////////////////////////////
    /// @param resource_path path to the resource for the network
    Network(const std::filesystem::path& resource_path);

    ///////////////////////////////////////////////////////////////
    /// @brief create a list of station from a list of station_name
    /// @param station_name_list a list of station to find the
    /// @return a list of station reference
    std::vector<Station_CRef> Get_Station_Reference(std::vector<std::string> station_name_list);

    ///////////////////////////////////////////
    /// @brief give back all the line that pass through a station for the specified day
    /// @param station the station to find passing line
    /// @param day the day where to look for
    /// @return a list of reference to the passing line
    std::vector<Line_CRef> Get_Passing_Lines(const Station& station, const Day& day);
    
    /////////
    ///getter
    const std::vector<Line>& Get_Lines() const noexcept;
    const std::vector<Station>& Get_Station() const noexcept;
private:
    std::vector<Station> m_station_list;
    std::vector<Line> m_line_list;
};


#endif //NETWORK_H