#include "includes/map/image.h"

// STD
#include <algorithm>
#include <ranges>

// Context
#include "includes/context/reach_algorithm.h"
#include "includes/context/station.h"

// Network
#include "includes/network/station.h"

// Utils
#include "includes/utils/planar_coordinate.h"
#include "includes/utils/exception_def.h"
#include "includes/utils/daytime.h"


static Utils::Integer_Rectangle Compute_Network_Boundary(const std::vector<Network::Station>& stations)
{
    if (!stations.size())
        THROW(SIZE_IS_ZERO);

    std::vector<std::reference_wrapper<const Sphere_Coordinate>> coordinates;
    coordinates.reserve(stations.size());
    for (const Network::Station& station : stations)
        coordinates.emplace_back(std::ref(station.GetCoordinate()));
    Planar_Coordinate::Compute_Mean_Longitude_Factor(coordinates);

    Planar_Coordinate coordinate(stations[0].GetCoordinate());
    double x_min = coordinate.Get_X();
    double x_max = coordinate.Get_X();
    double y_min = coordinate.Get_Y();
    double y_max = coordinate.Get_Y();

    for (const Network::Station& station : stations)
    {
        Planar_Coordinate station_coordinate(station.GetCoordinate());
        if (station_coordinate.Get_X() < x_min)
            x_min = station_coordinate.Get_X();
        if (station_coordinate.Get_X() > x_max)
            x_max = station_coordinate.Get_X();
        if (station_coordinate.Get_Y() < y_min)
            y_min = station_coordinate.Get_Y();
        if (station_coordinate.Get_Y() > y_max)
            y_max = station_coordinate.Get_Y();
    }
    return Utils::Integer_Rectangle((size_t)x_min, (size_t)x_max,(size_t)y_min,(size_t)y_max);
}


Map::Image::Image(const Context::Reach_Algorithm& context, const std::vector<Context::Station>& optimized_station, double resoltuion_per_pixel) :
    m_boundary(Compute_Network_Boundary(context.GetNetwork().Get_Station())),
    m_meter_per_pixel(resoltuion_per_pixel),
    m_stations(optimized_station),
    m_reach_context(context)
{

}

DayTime Map::Image::Compute_Time_To_Coordinate(const Network::Station& station, const Planar_Coordinate& coordinate) const noexcept
{
    return this->Compute_Time_To_Coordinate(Planar_Coordinate(station.GetCoordinate()), coordinate);
}

DayTime Map::Image::Compute_Time_To_Coordinate(const Planar_Coordinate& coordinate1, const Planar_Coordinate& coordinate2) const noexcept
{
    return coordinate1.Get_Distance(coordinate2) * m_reach_context.get().Get_Speed();
}

std::vector<std::vector<DayTime>> Map::Image::Compute_Time_Image()
{

    std::vector<std::vector<DayTime>> image(size_t(m_boundary.Get_Y_Length() / m_meter_per_pixel), std::vector<DayTime>(size_t(m_boundary.Get_X_Length() / m_meter_per_pixel),0));
    auto range_x = std::views::iota(size_t(0), size_t(m_boundary.Get_X_Length()/m_meter_per_pixel));
    auto range_y = std::views::iota(size_t(0), size_t(m_boundary.Get_Y_Length()/m_meter_per_pixel));
    std::for_each(range_x.begin(), range_x.end(), [&](size_t i) {
        std::for_each(range_y.begin(), range_y.end(), [&](size_t j) {
            auto temp = Planar_Coordinate(double(i) * m_meter_per_pixel + m_boundary.Get_X_Min(),double(j) * m_meter_per_pixel + m_boundary.Get_Y_Min());
            DayTime min = this->Compute_Time_To_Coordinate(temp, Planar_Coordinate(m_reach_context.get().Get_Starting_Coordinate()));
            for (const Context::Station& station : m_stations.get())
            {
                DayTime distance = this->Compute_Time_To_Coordinate(station.Get(), temp);
                if (distance < min)
                    min = distance;
            }
            image[j][i] = min;
        });
    });
    return image;
}



