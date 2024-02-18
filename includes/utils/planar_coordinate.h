#ifndef UTILS_PLANAR_COORDINATE_H
#define UTILS_PLANAR_COORDINATE_H

namespace Context { class Scheduled_Network; };

class Planar_Coordinate
{
    ////////
    /// CTOR
public:
    Planar_Coordinate(const Sphere_Coordinate&) noexcept;

    ///////////
    /// METHODS
public:
    size_t Get_X() const noexcept;
    size_t Get_Y() const noexcept;

public:
    static void Compute_Mean_Longitude_Factor(const Context::Scheduled_Network& stations);


    //////////////
    /// ATTRIBTUES
private:
    size_t m_x;
    size_t m_y;
    static double s_mean_longitude_factor;
};

#endif //UTILS_PLANAR_COORDINATE_H