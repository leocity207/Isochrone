#ifndef LINE_H
#define LINE_H

#include <vector>

#include "includes/network_optimizer/schedule.h"

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
        bool Contain(const Station& station_to_find,const Day& day_template);
        

    
};

#endif //LINE_H