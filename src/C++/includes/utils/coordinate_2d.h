#ifndef COORDINATE_2D_H
#define COORDINATE_2D_H



struct Sphere_Coordinate
{
    float lattitude;
    float longitude;
    static constexpr int earth_radius = 6339000; 
};

struct Planar_Coordinate
{
    float x;
    float y;
    static float mean_x;
    static float mean_y;

    float operator>>(const Planar_Coordinate);
};

#endif //2D_COORDINATE_H