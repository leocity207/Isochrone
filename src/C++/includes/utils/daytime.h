#ifndef DAYTIME_H
#define DAYTIME_H

#include <chrono>
#include <functional>
#include <optional>

class DayTime
{
    public:
        DayTime() = default;
        DayTime(const DayTime& other) noexcept;
        DayTime(std::chrono::hours hours, std::chrono::minutes minutes) noexcept;
        
        bool operator==(const DayTime& other_DayTime) const noexcept;
        bool operator>(const DayTime& other_DayTime) const noexcept;
        bool operator<(const DayTime& other_DayTime) const noexcept;
        bool operator>=(const DayTime& other_DayTime) const noexcept;
        bool operator<=(const DayTime& other_DayTime) const noexcept;

        DayTime operator+(const std::chrono::seconds&) const noexcept;

        ////////////////////////////
        /// @brief create a daytime from a string
        /// @param description a string in the form "MM:SS" if it contain only space return nullopt
        /// @return an optional containing the daytime representation of the string
        /// @throw throw a parsing error if the string is ill formed
        static std::optional<DayTime> From_Time_String(const std::string_view& description);

        const std::chrono::minutes& GetTime() const noexcept;
    private:
        std::chrono::minutes m_day_minute; 
};

typedef std::reference_wrapper<const DayTime> DayTime_CRef;

#endif 