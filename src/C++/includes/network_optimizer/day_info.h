#ifndef DAY_INFO
#define DAY_INFO

#include <array>
#include <Chrono>


//------------------------
// A day type designate the 
enum DAY_TYPE{
    SCHOOL_DAYS,
    VACATION_DAYS,
    HOLLY_DAY,
    COUNT
};

constexpr int WEEKDAY_COUNT = 7;
constexpr int DAY_TYPE_COUNT = static_cast<int>(DAY_TYPE::COUNT);


//-----------------------------------------
// This class is a representation of a Day
// A day is two thing:
//  - Weekday  should be referred using std::chrono::weekday )
//  - The type of day  (As described in the data type schedule above)
class Day
{
    public:
        Day() = delete;
        Day(const std::chrono::weekday,const DAY_TYPE) noexcept;
        

        const std::chrono::weekday& GetWeekday() const noexcept;
        const DAY_TYPE&             GetDayType() const noexcept;
        const std::string          Description() const noexcept;
    private:
        std::chrono::weekday m_weekday;
        DAY_TYPE m_day_type;
};

//-------------------------------------------------------------------------------------------
// This class represent a template Day that can be used to see if a day fit inside a template
// it generaly represent working schedule day
// A day is two thing:
//  - Weekday  should be referred using std::chrono::weekday )
//  - The type of day  (As described in the data type schedule above)
class DayTemplate
{
    public:
        DayTemplate() = delete;
        DayTemplate(const std::array<bool,WEEKDAY_COUNT>,const std::array<bool,DAY_TYPE_COUNT>) noexcept;
        DayTemplate(DayTemplate&&) noexcept;

        bool Match(const Day&) const noexcept;
    private:
        std::array<bool,WEEKDAY_COUNT> m_working_days;
        std::array<bool,DAY_TYPE_COUNT> m_working_types;
};

#endif //DAY_INFO