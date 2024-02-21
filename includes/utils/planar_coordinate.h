#ifndef UTILS_PLANAR_COORDINATE_H
#define UTILS_PLANAR_COORDINATE_H

// STD
#include <functional>

namespace Context { class Scheduled_Network; };
class Sphere_Coordinate;

class Planar_Coordinate
{
    ////////
    /// CTOR
public:
    Planar_Coordinate(const Sphere_Coordinate&) noexcept;
    Planar_Coordinate(double x, double y) noexcept;

    ///////////
    /// METHODS
public:
    double Get_X() const noexcept;
    double Get_Y() const noexcept;
    double Get_Distance(const Planar_Coordinate&) const noexcept;

    //////////////////
    /// STATIC METHODS
public:
    static void Compute_Mean_Factor(const std::vector<std::reference_wrapper<const Sphere_Coordinate>>& stations);


    //////////////
    /// ATTRIBTUES
private:
    double m_x;
    double m_y;
    static double s_mean_longitude_factor;
    static double s_mean_lattitude_factor;
};

#endif //UTILS_PLANAR_COORDINATE_H