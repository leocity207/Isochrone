#ifndef DAYTIME_H
#define DAYTIME_H

#include <chrono>
#include <functional>

class DayTime
{
    public:
        DayTime() = delete;
        DayTime(std::chrono::hours hours, std::chrono::minutes minutes) noexcept;
        bool operator>(const DayTime& other_DayTime) const noexcept;
        bool operator<(const DayTime& other_DayTime) const noexcept;
        bool operator>=(const DayTime& other_DayTime) const noexcept;
        bool operator<=(const DayTime& other_DayTime) const noexcept;
    private:
        std::chrono::minutes m_day_minute; 
};

typedef std::reference_wrapper<const DayTime> DayTime_CRef;

#endif 