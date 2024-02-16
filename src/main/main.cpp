#include "includes/resource/archive/plain.h"
#include "includes/context/scheduled_network.h"
#include "includes/context/reach_algorithm.h"
#include "includes/reach_algorithm/simple.h"
#include "includes/reach_algorithm/simple_with_map.h"
#include "includes/reach_algorithm/simple_par.h"
#include "includes/reach_algorithm/simple_with_map_par.h"

using namespace std::chrono;

#include <execution>

int main()
{
	
	
	std::filesystem::path path("C:/dev/Isochrone/Ressource/config.json");
	auto [stations, scheduled_lines] = Resource::Archive::Plaine::Parse_Scheduled_Network_Resource(std::move(path));
	Context::Scheduled_Network network_context(std::move(scheduled_lines), std::move(stations));

	auto t0 = high_resolution_clock::now();

	for (auto i : std::views::iota(0, 100))
	{
		i;
		auto range = std::views::iota(0, 1440);

		std::for_each(
			std::execution::par,
			range.begin(),
			range.end(),
			[&](int item)
			{
				Context::Reach_Algorithm solver_context(network_context, DayTime(hours(item / 60), minutes(item % 60)), 1, Sphere_Coordinate(4.8740833333333340, 45.521305555555557), Network::Day(Monday, Network::SCHOOL_DAYS));
				Reach_Algorithm::Simple_With_Map_Par algorithm;
				std::vector<Context::Station> result = solver_context.Optimize(algorithm);
			});

	}
	auto t1 = high_resolution_clock::now();
	milliseconds d = std::chrono::duration_cast<milliseconds>(t1-t0);
	std::cout << (t1 - t0).count() << "s\n";
	std::cout << d.count() / ((1260.0 - 480.0)*100) << "ms\n";

	Context::Reach_Algorithm solver_context(network_context, DayTime(hours(8), minutes(0)), 1, Sphere_Coordinate(4.8740833333333340, 45.521305555555557), Network::Day(Monday, Network::SCHOOL_DAYS));
	Reach_Algorithm::Simple_With_Map_Par algorithm;
	std::vector<Context::Station> result = solver_context.Optimize(algorithm);
	std::ofstream output("ouput.txt");
	for (const auto& station : result)
		output << station.Get().Get_Name() << ";" << station.Get_Reaching_Time().ToString() << ";" << station.Has_Been_Reached_By_Transport() << ";" << station.Has_Been_Reached_Once_By_Transport() << std::endl;


	return 0;
}