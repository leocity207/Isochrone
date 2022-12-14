#ifndef SCHEDULE_H
#define SCHEDULE_H


#include <vector>

//utils
#include "includes/utils/daytime.h"

//network_optimization
#include "includes/network_optimizer/station.h"
#include "includes/network_optimizer/day_info.h"


//------------------------------------------------------------------------------------------------------------
// Schedule class represent transport schedule and meta data about the schedule
// Basicaly We suppose a schedule is a matrix containing the time at which the transport get to the station
// Here we suppose that the line represent the station and the column represent the pathway of one transport
// Needed meta data are as follow:

typedef std::vector<std::vector<DayTime>> TimeTable;
class Schedule : public DayTemplate
{
    public:
        Schedule() = delete;
        Schedule(std::vector<Station&>&& station_list, TimeTable&& schedule_tab,DayTemplate&& day_template) noexcept;

        bool Contain(const Station& station_to_find);
        bool Order(const Station& first,const Station& second) noexcept const;
    private:
        std::vector<Station&> m_station_list;
        TimeTable m_schedule;
};

#endif //SCHEDULE_H