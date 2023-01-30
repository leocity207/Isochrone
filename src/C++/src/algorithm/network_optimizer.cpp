#include "includes/algorithm/network_optimizer.h"
#include "includes/algorithm/algorithm_station.h"

#include <algorithm>
#include <ranges>
#include <cassert>
#include <map>
#include <execution>

Network_Optimizer::Network_Optimizer(const Network& network,const Sphere_Coordinate& start_coordinate,const double default_speed,const DayTime& start_time,const Day& day_type) noexcept : m_network(network), m_start_coordinate(start_coordinate), m_speed(default_speed), m_start_time(start_time), m_day_type(day_type)
{

}


const DayTime& Network_Optimizer::Get_Start_Time() const noexcept 
{
    return m_start_time;
}

const double Network_Optimizer::Get_Speed() const noexcept 
{
    return m_speed;
}

const Sphere_Coordinate& Network_Optimizer::Get_Start_Coordinate() const noexcept 
{
    return m_start_coordinate;
}


std::vector<Algorithm_Station> Network_Optimizer::Optimize()
{
    
    std::list<Algorithm_Station> station_list;
    std::vector<Algorithm_Station> final_optimized;
    const std::list<Algorithm_Station>::iterator* best_item = nullptr;
    std::map < Station_CRef, std::reference_wrapper<Algorithm_Station>, std::less<const Station>> smap;

    for (const Station& station : m_network.Get_Station())
    {
        station_list.emplace_back(station, *this);
        station_list.back().SetPos(--station_list.end());
        smap.insert({ station, station_list.back() });

        if (!best_item || (*best_item)->Get_Reach_Time() > station_list.back().Get_Reach_Time())
            best_item = &(station_list.back().Get_Pos());
    }


    /////////////////////////
    // run throug all station
    // O(S)
    for(size_t i = station_list.size()-1;i--;)
    {
        //order list and pop the best element;
        final_optimized.emplace_back(std::move(**best_item));
        station_list.erase(*best_item);
        best_item = nullptr;
        Algorithm_Station& current_station = final_optimized.back();

        
        ///////////////////////////////////////////////////////////////////
        //get list of lines passing at the choosen station
        // O(L)
        // could be improved by cahcing the passing line inside the station
        auto line_list = std::views::filter(m_network.Get_Lines(), [&](const Line& line) {
            return line.Contain(current_station.Get(),m_day_type);
        });

        //////////////////////////////////////////////////////////////////////
        // Check for reaching station by base speed
        // passage to this function is mandatory to update the best time value
        // Sequential is O(S)
        // Parallele is O(1)
        std::for_each(std::execution::seq, station_list.begin(), station_list.end(), [&](Algorithm_Station& alg_station) {
            std::chrono::seconds default_time((int)std::round(current_station.Get().Get_Distance_To(alg_station.Get()) / m_speed));
            DayTime time = current_station.Get_Reach_Time() + default_time;
            alg_station.Try_Set_New_Best_Time_Base(time);
            if(!best_item || alg_station.Get_Reach_Time() < (*best_item)->Get_Reach_Time())
                best_item = &(alg_station.Get_Pos());
        });

        //////////////////////////////////////////////////////////////////
        /// For all lines passing by the station
        /// At worst O(L) but more like the mean station passing by a line
        /// Paralelisable if each line don't meet
        std::for_each(line_list.begin(), line_list.end(), [&](const Line& line) {
            /////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// Get the right schedules for that day (could be cached)
            /// Complexcity is equivalent to the number of schedule wich is constant around at most 8 for some station
            const std::array<Schedule_CRef,2> schedule_list = line.Get_Schedules(m_day_type);
            /////////////////////////////////////////////////////////////////////////////////////////////
            /// Constant for the line and parralelisable for a specific line the size should always be 2 
            std::for_each(schedule_list.begin(), schedule_list.end(), [&](const Schedule& schedule) {
                //////////////////////////////////////////////////////////////////////
                ///go for all station inside the line (this could be improved because )
                std::for_each(schedule.From_Station(current_station.Get()), schedule.Get_Station_List().cend(), [&](const Station_CRef& station) {
                    //no need to compute distance from the two same station
                    std::optional<DayTime> value = schedule.Get_Closest_Time_To_Station(current_station, station.get());
                    Algorithm_Station& end_alg_station = smap.at(station).get();
                    //auto pose = std::find_if(station_list.begin(), station_list.end(), [&](const Algorithm_Station& alg_station) {return alg_station.Get() == station; });
                    if ((end_alg_station.Try_Set_New_Best_Time_Transport(value) && value<(*best_item)->Get_Reach_Time()))
                         best_item = &(end_alg_station.Get_Pos());
                });
            });
        });

    }

    //dont forget the last element
    final_optimized.emplace_back(std::move(station_list.back()));
    return final_optimized;
}