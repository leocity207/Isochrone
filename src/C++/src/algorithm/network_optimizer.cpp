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
    std::list<Algorithm_Station>::iterator& best_item = station_list.begin();

    for (const Station& station : m_network.Get_Station())
    {
        station_list.emplace_back(&station, this);
        if (best_item->Get_Reach_Time() > station_list.back().Get_Reach_Time())
            best_item = station_list.end();
    }



    for(size_t i = station_list.size()-1;i--;)
    {
        //order list and pop the best element;
        final_optimized.emplace_back(std::move(*best_item));
        station_list.erase(best_item);
        Algorithm_Station& current_station = final_optimized.back();

        //get list of lines passing at the choosen station
        auto line_list = std::views::filter(m_network.Get_Lines(), [&](const Line& line) {
            return line.Contain(current_station.Get(),m_day_type);
        });

        std::for_each(std::execution::seq,station_list.begin(), station_list.end(), [&](Algorithm_Station& alg_station) {
            std::chrono::seconds default_time((int)std::round(current_station.Get().Get_Distance_To(alg_station.Get()) / m_speed));
            DayTime time = current_station.Get_Reach_Time() + default_time;
            alg_station.Try_Set_New_Best_Time(time);
        });
        if(current_station.Has_Been_Reached_By_Transport())
            for (Algorithm_Station& alg_station : station_list)
            {
                std::chrono::seconds default_time((int)std::round(current_station.Get().Get_Distance_To(alg_station.Get())/m_speed));
                DayTime time = current_station.Get_Best_Time_Start_To_Station() + default_time;
                alg_station.Try_Set_New_Best_Time_Base(time);
            }

        //for all lines passing by the station
        std::for_each(std::execution::seq,line_list.begin(), line_list.end(), [&](const Line& line) {
            auto schedule_list = line.Get_Schedules(m_day_type);
            //get the right schedules for that day
            std::for_each(std::execution::seq,schedule_list.begin(), schedule_list.end(), [&](const Schedule& schedule) {
                //for all station in the lines
                std::for_each(std::execution::seq,schedule.Get_Station_List().begin(), schedule.Get_Station_List().end(), [&](const Station_CRef& station) {
                    //no need to compute distance from the two same station
                    if (station.get() != current_station.Get()) 
                    {
                        std::optional<DayTime> value = schedule.Get_Closest_Time_To_Station(current_station, station.get());
                        auto pose = std::find_if(station_list.begin(), station_list.end(), [&](const Algorithm_Station& alg_station) {return alg_station.Get() == station; });
                        if (pose != station_list.end() && pose->Try_Set_New_Best_Time_Transport(value) && value<best_item->Get_Reach_Time())  
                            best_item = pose;
                    }
                });
            });
        });

    }

    //dont forget the last element
    final_optimized.emplace_back(std::move(station_list.back()));
    return final_optimized;
}