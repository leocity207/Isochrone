#include "includes/resource/csv/validator/timetable.h"

#include <ranges>

using namespace std::chrono;

CSV::Parser::Validator::TimeTable_Error_Time::TimeTable_Error_Time(size_t i, size_t j, DayTime time, const std::string& name) noexcept :
	CSV::Parser::Validator::TimeTable_Error(),
	m_i(i),
	m_j(j),
	m_time(time),
	m_name(name)
{

}

CSV::Parser::Validator::TimeTable_Error_Size::TimeTable_Error_Size(size_t normal_size, size_t anormal_size, size_t i, const std::string& name) noexcept :
	CSV::Parser::Validator::TimeTable_Error(),
	m_i(i),
	m_normal_size(normal_size),
	m_anormal_size(anormal_size),
	m_name(name)
{

}

std::string CSV::Parser::Validator::TimeTable_Error_Time::Get_Error_As_String() const noexcept
{
	return std::string("Line: ") + m_name + " at time " + m_time.ToString() + " coordinate : " + std::to_string(m_i) + ":" + std::to_string(m_j);
}

const size_t CSV::Parser::Validator::TimeTable_Error_Time::Get_i() const noexcept
{
	return m_i;
}

const size_t CSV::Parser::Validator::TimeTable_Error_Time::Get_j() const noexcept
{
	return m_j;
}

const DayTime CSV::Parser::Validator::TimeTable_Error_Time::Get_Time() const noexcept
{
	return m_time;
}

std::string CSV::Parser::Validator::TimeTable_Error_Size::Get_Error_As_String() const noexcept
{
	return "Line: " + m_name + " at line " + std::to_string(m_i) + " expected size : " + std::to_string(m_normal_size) + " but got size " + std::to_string(m_anormal_size);
}

const size_t CSV::Parser::Validator::TimeTable_Error_Size::Get_i() const noexcept
{
	return m_i;
}

const size_t CSV::Parser::Validator::TimeTable_Error_Size::Get_Anormal_Size() const noexcept
{
	return m_anormal_size;
}

const size_t CSV::Parser::Validator::TimeTable_Error_Size::Get_Normal_Size() const noexcept
{
	return m_normal_size;
}

std::vector<std::unique_ptr<CSV::Parser::Validator::TimeTable_Error>> CSV::Parser::Validator::Validate(const TimeTable& timetable,const std::string& name) noexcept
{
	std::vector<std::unique_ptr<CSV::Parser::Validator::TimeTable_Error>> errors;
	if (!timetable.size())
		return errors;
	const size_t normal_size = timetable.begin()->size();
	for (size_t i : std::views::iota(size_t(0), timetable.size()))
	{
		if (timetable[i].size() != normal_size)
			errors.push_back(std::unique_ptr< CSV::Parser::Validator::TimeTable_Error>(new CSV::Parser::Validator::TimeTable_Error_Size(normal_size, timetable[i].size(), i, name)));
		DayTime current_daytime(0h,0min);
		for (size_t j : std::views::iota(size_t(0), timetable[i].size()))
			if (!timetable[i][j].has_value())
				continue;
			else if (timetable[i][j] < current_daytime)
				errors.push_back(std::make_unique<CSV::Parser::Validator::TimeTable_Error_Time>(i, j, *timetable[i][j], name));
			else
				current_daytime = *timetable[i][j];
	}
	return errors;
}
