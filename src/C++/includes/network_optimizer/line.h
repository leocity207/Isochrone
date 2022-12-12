#ifndef LINE_H
#define LINE_H

#include <vector>

#include "includes/network_optimizer/schedule.h"
#include "submodule/Logger/includes/exception.h"

DECLARE_EXCEPTION(Exception,Station_Not_In_Line,"One of the station is not in the current line.");
DECLARE_EXCEPTION(Exception,No_Matching_Schedule,"No Schedule was found for the day");

class Line
{
    private:
        std::string m_name;
        int m_id;
        std::vector<Schedule> m_schedule;
        static int s_count;
    public:
        Line() = delete;
        Line(std::vector<Schedule>&& Schedule,std::string&& name) noexcept;
        DayTime& Get_Best_Time_To_Station(const Station& start_station,const Station& end_station,const DayTime& current_time,const Day& day_template) const;
        bool Contain(const Station& station_to_find,const Day& day_template) noexcept(false) const;
        const Schedule& Get_Schedule(const Day& matching_day) noexcept(false) const;
        

    
};

#endif //LINE_H