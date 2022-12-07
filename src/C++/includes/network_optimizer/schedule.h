#ifndef SCHEDULE_H
#define SCHEDULE_H


#include <vector>
#include <chrono>

enum DAY_TYPE{
    SCHOOL_DAYS,
    VACATION_DAYS,
    HOLLY_DAY,
    COUNT
};
class Schedule
{
    private:
    std::array<bool,7> m_working_days;
    std::array<bool,static_cast<int>(DAY_TYPE::COUNT)> m_working_types;
    std::vector<std::vector<std::chrono::hh_mm_ss>> m_schedule;
    public:

    operator==();
    
}

#endif //SCHEDULE_H