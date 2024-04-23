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
	/////////////////////////////////////////////////////////////////////////
	/// @brief A day type designate typical running day of a transport network 
	enum DAY_TYPE {
		SCHOOL_DAYS,
		VACATION_DAYS,
		HOLYDAYS,
		COUNT
	};

	constexpr int WEEKDAY_COUNT = 7;
	constexpr int DAY_TYPE_COUNT = static_cast<int>(DAY_TYPE::COUNT);

	///////////////////////////////////////////////////////////////////////////////
	/// @brief This class is a representation of a Day
	///        A day is two thing:
	///            * Weekday  should be referred using std::chrono::weekday )
	///            * The type of day  (As described in the data type schedule above)
	/// @note default_constructible
	///       copy_constructible
	///       copy_assignable
	///       move_constructible
	///       move_asignable
	class Day
	{
		//#####
		// CTOR
		public:
			DELETE_DEFAULT_CTOR(Day);

			///////////////////////////////
			/// @brief Explicit constructor
			Day(const std::chrono::weekday, const DAY_TYPE) noexcept;

		//########
		// METHODS
		public:
			/////////////////////////
			/// @brief Equality operator
			bool operator==(const Day& other) const noexcept;

			///////////////////////////////////////////////
			/// @brief Give back the weekday of the Day
			const std::chrono::weekday& GetWeekday() const noexcept;

			/////////////////////////////////////////////////
			/// @brief Give backe the day type of the Day
			const DAY_TYPE& GetDayType() const noexcept;

			////////////////////////////////////////
			/// @brief Readable description of the Day 
			const std::string Description() const noexcept;

		//###########
		// ATTRIBUTES
		private:
			std::chrono::weekday m_weekday;
			DAY_TYPE m_day_type;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class represent a template Day that can be used to see if a day fit inside a template
	///        It generaly represent working schedule day
	///        A day is two thing:
	///            * Weekday  should be referred using std::chrono::weekday )
	///            * The type of day  (As described in the data type schedule above)
	/// @note not_default_constructible
	///       not_copy_constructible
	///       not_copy_assignable
	///       move_constructible
	///       move_asignable
	class DayTemplate
	{
		//#####
		// CTOR
		public:
			DELETE_DEFAULT_CTOR(DayTemplate);
			DEFAULT_MOVE(DayTemplate);
			DELETE_COPY(DayTemplate);

			///////////////////////////////
			/// @brief Explicit constructor
			DayTemplate(const std::array<bool, WEEKDAY_COUNT>, const std::array<bool, DAY_TYPE_COUNT>) noexcept;

		//########
		// METHODS
		public:
			//////////////////////////////////////////////////////////
			/// @brief     See if the day is a match for the day day 
			/// @param day To see if contained by this day template
			/// @return    Wether or not the day is contained by the day template
			bool Match(const Day& day) const noexcept;

			//////////////////////////////////////////////////////////////////////
			/// @brief See if the other DayTemplate is strictly equal to the other
			bool operator==(const DayTemplate& other) const noexcept;

		//###########
		// ATTRIBUTES
		private:
			std::array<bool, WEEKDAY_COUNT> m_working_days;
			std::array<bool, DAY_TYPE_COUNT> m_working_types;
	};

}// Network

#endif //NETWORK_DAY_INFO