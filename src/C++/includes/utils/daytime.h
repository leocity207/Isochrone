#ifndef DAYTIME_H
#define DAYTIME_H

#include <chrono>
#include <functional>
#include <optional>

class DayTime
{
    public:
        DayTime() = delete;
        DayTime(std::chrono::hours hours, std::chrono::minutes minutes) noexcept;
        bool operator>(const DayTime& other_DayTime) const noexcept;
        bool operator<(const DayTime& other_DayTime) const noexcept;
        bool operator>=(const DayTime& other_DayTime) const noexcept;
        bool operator<=(const DayTime& other_DayTime) const noexcept;

        static std::optional<DayTime> From_Time_String(const std::string_view& description);

        const std::chrono::minutes& GetTime();
    private:
        std::chrono::minutes m_day_minute; 
};

typedef std::reference_wrapper<const DayTime> DayTime_CRef;

#endif 