#include "includes/network/scheduled_line.h"


#include <algorithm>
#include <ranges>


Network::Scheduled_Line::Scheduled_Line(std::vector<Network::Schedule>&& Timetable, std::string&& name) noexcept :
	Line(Scheduled_Line::Construct_Station_From_Schedules(m_schedule), std::move(name)),
	m_schedule(std::move(Timetable))
{

}

std::optional<DayTime_CRef> Network::Scheduled_Line::Get_Closest_Time_To_Station(const Station& start_station, const Network::Station& end_station, const DayTime& start_station_time, const Network::Day& matching_day) const noexcept
{
	std::optional<Schedule_CRef> selected_schedule = this->Get_Schedule(matching_day, start_station, end_station);
	if (!selected_schedule.has_value())
		return std::nullopt;
	return selected_schedule->get().Get_Closest_Time_To_Station(start_station, end_station, start_station_time);
}

std::optional<Network::Schedule_CRef> Network::Scheduled_Line::Get_Schedule(const Network::Day& matching_day, const Network::Station& start_station, const Network::Station& end_station) const noexcept
{
	auto start_station_ref = std::reference_wrapper<const Station>(start_station);
	auto end_station_ref = std::reference_wrapper<const Station>(end_station);
	auto does_day_match_schedule = [matching_day, start_station_ref, end_station_ref](const Network::Schedule& i) { 
			try {
				return i.Match(matching_day) && (i.Order(start_station_ref, end_station_ref) == std::strong_ordering::less);
			}
			catch (STATION_NOT_IN_SCHEDULE&)
			{
				return false;
			}
		};

	std::vector<Schedule_CRef> transformed(m_schedule.begin(), m_schedule.end());
	auto right_schedule = std::find_if(transformed.begin(), transformed.end(), does_day_match_schedule);
	if (right_schedule == transformed.end())
		TRACE_RETURN("[warning]", std::nullopt, "The line" , m_name , "have no schedule for " , matching_day.Description());
	return m_schedule[right_schedule - transformed.begin()];
}

bool Network::Scheduled_Line::Contain(const Network::Station& station, const Network::Day& matching_day) const noexcept
{
	std::reference_wrapper<const Station> station_ref = station;
	auto temp = this->Get_Schedules(matching_day);
	return std::any_of(temp.begin(), temp.end(), [station_ref](const Network::Schedule& schedule) {return schedule.Contain(station_ref); });
}

std::vector<Network::Station_CRef> Network::Scheduled_Line::Construct_Station_From_Schedules(const std::vector<Schedule>&)
{
	return std::vector<Station_CRef>();
}