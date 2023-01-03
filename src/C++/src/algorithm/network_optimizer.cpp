#include "includes/algorithm/network_optimizer.h"
#include "includes/algorithm/algorithm_station.h"

#include <algorithm>
#include <ranges>
#include <cassert>
#include <map>
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
    std::vector<Algorithm_Station> station_list;
    std::vector<Algorithm_Station> final_optimized;
    std::map<const Station*,Algorithm_Station*> map_station;
    station_list.reserve(m_network.Get_Station().size());

    //initialize station_list;
    for (const Station& station : m_network.Get_Station())
    {
        station_list.emplace_back(&station, this);
        map_station.insert(std::make_pair(&station, &station_list.back()));
    }

    for(size_t i = station_list.size()-1;i--;)
    {
        //order list and pop the best element;
        std::make_heap(station_list.begin(), station_list.end());
        std::pop_heap(station_list.begin(), station_list.end());
        final_optimized.emplace_back(std::move(station_list.back()));
        station_list.pop_back();
        Algorithm_Station& current_station = final_optimized.back();

        //get list of lines passing at the choosen station
        auto line_list = std::views::filter(m_network.Get_Lines(), [&](const Line& line) { return line.Contain(current_station.Get(),m_day_type);});

        //for all lines passing by the station
        std::for_each(line_list.begin(), line_list.end(), [&](const Line& line) { 
            auto schedule_list = line.Get_Schedules(m_day_type);
            //get the right schedules for that day
            std::for_each(schedule_list.begin(), schedule_list.end(), [&](const Schedule& schedule) { 
                //for all station in the lines
                std::for_each(schedule.Get_Station_List().begin(), schedule.Get_Station_List().end(), [&](const Station_CRef& station) { 
                    //no need to compute distance from the two same station
                    if (station.get() != current_station.Get()) 
                    {
                        std::optional<DayTime> value = schedule.Get_Closest_Time_To_Station(current_station, station.get());
                        map_station.at(&(station.get()))->Try_Set_New_Best_Time(value);
                    }
                });
            });
        });

    }

    //dont forget the last element
    final_optimized.emplace_back(std::move(station_list.back()));
    return final_optimized;
}