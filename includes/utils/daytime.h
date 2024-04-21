#ifndef DAYTIME_H
#define DAYTIME_H

// STL
#include <chrono>
#include <optional>


////////////////////////////////////////////////////////////////////////
/// @brief wrapper around std::chrono in order to represent HH:MM values
/// @note  default_constructible
///        copy_constructible
///        copy_assignable
///        move_constructible
///        move_asignable
class DayTime
{
    public:
        DayTime() = default;
        DayTime(const DayTime& other) noexcept;
        DayTime(std::chrono::hours hours, std::chrono::minutes minutes) noexcept;
        
        //////////////////////////////////////////////////////
        /// @brief mathematical operator on times
        /// @note this class is not cyclic therfore time like 27:45 can exist
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
        /// @throw "TIME_BADLY_FORMATED" a parsing error if the string is ill formed
        static std::optional<DayTime> From_Time_String(const std::string_view& description);

        ////////////////////////////////////////
        /// @brief Give back the time in minutes
        /// @return std::chrono::minutes representation of DayTime object
        std::chrono::minutes GetTime() const noexcept;

        //////////////////////////////////////////////
        /// @brief Give a string like 'HH:MM'
        /// @return An readable std::string object of format 'HH:MM'
        const std::string ToString() const noexcept;
    private:

        DayTime(std::chrono::seconds seconds) noexcept;
        std::chrono::seconds m_day_seconds; 
};

using DayTime_CRef = std::reference_wrapper<const DayTime>;

#endif 