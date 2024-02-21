#include "includes/resource/archive/plain.h"
#include "includes/context/scheduled_network.h"
#include "includes/context/reach_algorithm.h"
#include "includes/reach_algorithm/simple.h"
#include "includes/reach_algorithm/simple_with_map.h"
#include "includes/reach_algorithm/simple_par.h"
#include "includes/reach_algorithm/simple_with_map_par.h"
#include "includes/map/image.h"

using namespace std::chrono;

#include <execution>

int main()
{
	
	
	std::filesystem::path path("C:/dev/Isochrone/Ressource/config.json");
	auto [stations, scheduled_lines] = Resource::Archive::Plaine::Parse_Scheduled_Network_Resource(std::move(path));
	Context::Scheduled_Network network_context(std::move(scheduled_lines), std::move(stations));

	auto t0 = high_resolution_clock::now();
	size_t j = 0;
	for (size_t i = 8 * 60 * 60; i < 20 * 60 * 60; i+=60)
	{

		Context::Reach_Algorithm solver_context(network_context, DayTime((double)i), 1, Sphere_Coordinate(4.8740833333333340, 45.521305555555557), Network::Day(Monday, Network::SCHOOL_DAYS));
		Reach_Algorithm::Simple_With_Map algorithm;
		std::vector<Context::Station> result = solver_context.Optimize(algorithm);
		Map::Image map_creator(solver_context, result, 50);
		auto map = map_creator.Compute_Time_Image();




		auto t1 = high_resolution_clock::now();
		milliseconds d = std::chrono::duration_cast<milliseconds>(t1 - t0);
		std::cout << (t1 - t0).count() << "s\n";
		std::cout << d.count() / (1260.0 - 480.0) << "ms\n";


		std::ofstream output("output"+std::to_string(j) + ".img");
		for (const auto& rows : map)
		{
			for (size_t s = 0; s < rows.size(); s++)
			{
				if (s != 0)
					output << ",";
				output << rows[s].GetTime().count();
			}
			output << std::endl;
		}
		j++;
	}

		

	return 0;
}