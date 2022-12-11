#ifndef DAYTIME_H
#define DAYTIME_H

#include <chrono>

class DayTime
{
    public:
        DayTime() = delete;
        DayTime(std::chrono::hours hours, std::chrono::minutes minutes) noexcept;
    private:
        std::chrono::minutes m_day_minute; 
};

#endif