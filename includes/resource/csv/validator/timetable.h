#ifndef CSV_PARSER_VALIDATOR_H
#define CSV_PARSER_VALIDATOR_H


// Utils
#include "includes/utils/daytime.h"
#include "includes/utils/ctor.h"

// Ressource
#include "includes/resource/csv/engine/parser.h"

using  TimeTable = std::vector<std::vector<std::optional<DayTime>>>;


namespace CSV
{
	namespace Parser
	{
		namespace Validator
		{
			class TimeTable_Error
			{
				//#####
				// CTOR
			public:
				DELETE_COPY(TimeTable_Error)
				DELETE_MOVE(TimeTable_Error)
				VIRTUAL_DESTRUCTOR(TimeTable_Error)
				TimeTable_Error() = default;

				//########
				// Methods
			public:
				virtual std::string Get_Error_As_String() const noexcept = 0;

			};

			class TimeTable_Error_Time : public TimeTable_Error
			{
				//#####
				// CTOR
				public:
					DELETE_COPY(TimeTable_Error_Time)
					DELETE_DEFAULT_CTOR(TimeTable_Error_Time)
					DELETE_MOVE(TimeTable_Error_Time)
					TimeTable_Error_Time(size_t i,size_t j,DayTime time,const std::string& name) noexcept;
				
				//########
				// Methods
				public:
					std::string Get_Error_As_String() const noexcept override;
					const size_t Get_i() const noexcept;
					const size_t Get_j() const noexcept;
					const DayTime Get_Time() const noexcept;
				
				//###########
				// ATTRIBUTES
				private:
					size_t m_i;
					size_t m_j;
					DayTime m_time;
					std::string m_name;
			};

			class TimeTable_Error_Size : public TimeTable_Error
			{
				//#####
				// CTOR
			public:
				DELETE_COPY(TimeTable_Error_Size)
				DELETE_DEFAULT_CTOR(TimeTable_Error_Size)
				DELETE_MOVE(TimeTable_Error_Size)
				TimeTable_Error_Size(size_t normal_size, size_t anormal_size, size_t i, const std::string& name) noexcept;

				//########
				// Methods
			public:
				std::string Get_Error_As_String() const noexcept override;
				const size_t Get_i() const noexcept;
				const size_t Get_Anormal_Size() const noexcept;
				const size_t Get_Normal_Size() const noexcept;

				//###########
				// ATTRIBUTES
			private:
				size_t m_i;
				size_t m_normal_size;
				size_t m_anormal_size;
				std::string m_name;
			};

			std::vector<std::unique_ptr<TimeTable_Error>> Validate(const TimeTable& timetable,const std::string&) noexcept;
		};

	}; // Parser

}; // CSV


#endif //CSV_PARSER_TIMETABLE_H