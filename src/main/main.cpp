#include "includes/resource/archive/plain.h"
#include "includes/context/scheduled_network.h"
#include "includes/context/reach_algorithm.h"
#include "includes/reach_algorithm/optimized.h"

using namespace std::chrono;

#include  <algorithm>
#include <execution>

int main()
{
	
	
	std::filesystem::path path("C:/dev/Isochrone/Ressource/config.json");
	auto [stations, scheduled_lines] = Resource::Archive::Plaine::Parse_Scheduled_Network_Resource(std::move(path));
	Context::Scheduled_Network network_context(std::move(scheduled_lines), std::move(stations));

	auto t0 = high_resolution_clock::now();

	auto range = std::views::iota(0, 1000);

	std::for_each(
		std::execution::par,
		range.begin(),
		range.end(),
		[&](int item)
		{
			Context::Reach_Algorithm solver_context(network_context, DayTime(hours(item / 60), minutes(item % 60 )), 1, Sphere_Coordinate(45.52700, 4.878250), Network::Day(Monday, Network::SCHOOL_DAYS));
			Reach_Algorithm::Optimized algorithm;
			std::vector<Context::Station> result = solver_context.Optimize(algorithm);
		});


	auto t1 = high_resolution_clock::now();
	milliseconds d = std::chrono::duration_cast<milliseconds>(t1-t0);
	std::cout << (t1 - t0).count() << "s\n";
	std::cout << d.count() << "ms\n";
	return 0;
}