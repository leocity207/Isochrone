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
		/////////////////////////////////////////////////////////////////
		/// @brief validator are used to detect error inside the schedule
		namespace Validator
		{
			//////////////////////////////////
			/// @brief General Timetable Error
			/// @note  default_constructible
			///        not_copy_constructible
			///        not_copy_assignable
			///        not_move_constructible
			///        not_move_asignable
			class TimeTable_Error
			{
				//#####
				// CTOR
			public:
				DELETE_COPY(TimeTable_Error)
				DELETE_MOVE(TimeTable_Error)
				VIRTUAL_DESTRUCTOR(TimeTable_Error)
				DEFAULT_DEFAULT_CTOR(TimeTable_Error)

				//########
				// Methods
			public:
				///////////////////////////////////////////////////////////////////////////////
				/// @brief get the error as a string representation that could be added to logs
				virtual std::string Get_Error_As_String() const noexcept = 0;

			};

			//////////////////////////////////
			/// @brief General Timetable Error
			/// @note  default_constructible
			///        not_copy_constructible
			///        not_copy_assignable
			///        not_move_constructible
			///        not_move_asignable
			class TimeTable_Error_Time : public TimeTable_Error
			{
				//#####
				// CTOR
				public:
					DELETE_COPY(TimeTable_Error_Time)
					DELETE_DEFAULT_CTOR(TimeTable_Error_Time)
					DELETE_MOVE(TimeTable_Error_Time)

					///////////////////////////////
					/// @brief      Explicit constructor
					/// @param i    The ith row of the timetable
					/// @param j    The jth column  of the timetable
					/// @param time The daytime that is not correct
					/// @param name A string to identify the schedule
					TimeTable_Error_Time(size_t i,size_t j,DayTime time,const std::string& name) noexcept;

				//########
				// Methods
				public:
					std::string Get_Error_As_String() const noexcept override;

					/////////////////////////////////////////////////////////////////
					/// @brief Getter function i being the ith row of the timetable
					const size_t Get_i() const noexcept;

					/////////////////////////////////////////////////////////////////
					/// @brief Getter function j being the jth column  of the timetable
					const size_t Get_j() const noexcept;

					/////////////////////////////////////////////////////////////////
					/// @brief Getter function giving the daytime that is not correct
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

				///////////////////////////////
				/// @brief              Explicit constructor
				/// @param normal_size  Expected size of the comlumn
				/// @param anormal_size Unexpected size of the comlumn
				/// @param i            I being the ith row of the timetable
				/// @param name         A string to identify the schedule
				TimeTable_Error_Size(size_t normal_size, size_t anormal_size, size_t i, const std::string& name) noexcept;

				//########
				// Methods
			public:
				std::string Get_Error_As_String() const noexcept override;

				/////////////////////////////////////////////////////////////////
				/// @brief Getter function i being the ith row of the timetable
				const size_t Get_i() const noexcept;

				/////////////////////////////////////////////////////////////////
				/// @brief Getter function that return the unexpected size value
				const size_t Get_Anormal_Size() const noexcept;

				/////////////////////////////////////////////////////////
				/// @brief Getter function that return the expected size
				const size_t Get_Normal_Size() const noexcept;

				//###########
				// ATTRIBUTES
			private:
				size_t m_i;
				size_t m_normal_size;
				size_t m_anormal_size;
				std::string m_name;
			};

			//////////////////////////////////////////////////////////////////////////////////
			/// @brief           Validate a timetable object
			/// @param timetable The timetable to validate
			/// @param name      Name of the timetable for easier identification in the error
			/// @return          List of error found. Return a void list if no error are found
			std::vector<std::unique_ptr<TimeTable_Error>> Validate(const TimeTable& timetable,const std::string& name) noexcept;
		};

	}; // Parser

}; // CSV


#endif //CSV_PARSER_TIMETABLE_H