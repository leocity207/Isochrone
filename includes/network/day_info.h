#ifndef NETWORK_DAY_INFO
#define NETWORK_DAY_INFO

// STL
#include <array>
#include <Chrono>
#include <string_view>

// Utils
#include "includes/utils/ctor.h"


namespace Network
{
    ///////////////////////////
    // A day type designate the 
    enum DAY_TYPE {
        SCHOOL_DAYS,
        VACATION_DAYS,
        HOLYDAYS,
        COUNT
    };

    constexpr int WEEKDAY_COUNT = 7;
    constexpr int DAY_TYPE_COUNT = static_cast<int>(DAY_TYPE::COUNT);

    //////////////////////////////////////////
    // This class is a representation of a Day
    // A day is two thing:
    //  - Weekday  should be referred using std::chrono::weekday )
    //  - The type of day  (As described in the data type schedule above)
    class Day
    {
        ////////
        /// CTOR
        public:
            DELETE_DEFAULT_CTOR(Day);
            Day(const std::chrono::weekday, const DAY_TYPE) noexcept;

        ///////////
        /// METHODS
        public:
            bool operator==(const Day& other) const noexcept;
            const std::chrono::weekday& GetWeekday() const noexcept;
            const DAY_TYPE& GetDayType() const noexcept;
            const std::string Description() const noexcept;

        //////////////
        /// ATTRIBUTES
        private:
            std::chrono::weekday m_weekday;
            DAY_TYPE m_day_type;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////
    // This class represent a template Day that can be used to see if a day fit inside a template
    // it generaly represent working schedule day
    // A day is two thing:
    //  - Weekday  should be referred using std::chrono::weekday )
    //  - The type of day  (As described in the data type schedule above)
    class DayTemplate
    {
        ////////
        /// CTOR
        public:
            DELETE_DEFAULT_CTOR(DayTemplate);
            DELETE_COPY(DayTemplate);

            DayTemplate(const std::array<bool, WEEKDAY_COUNT>, const std::array<bool, DAY_TYPE_COUNT>) noexcept;
            DayTemplate(DayTemplate&&) noexcept;

        ///////////
        /// METHODS
        public:
            //////////////////////////////////////////////////////////
            /// @brief see if the day is a match for the day day 
            /// @param day to see if contained by this day template
            /// @return wether or not the day is contained by the day template
            bool Match(const Day& day) const noexcept;

            bool operator==(const DayTemplate& other) const noexcept;

        //////////////
        /// ATTRIBUTES
        private:
            std::array<bool, WEEKDAY_COUNT> m_working_days;
            std::array<bool, DAY_TYPE_COUNT> m_working_types;
    };

}// Network

#endif //NETWORK_DAY_INFO