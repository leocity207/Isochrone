#ifndef COORDINATE_2D_H
#define COORDINATE_2D_H



class Sphere_Coordinate
{
    public:
        Sphere_Coordinate(double longitude,double latitude) noexcept;

        /////////////////////////////////////////////////////////////////////////////////////////
        /// @brief contructor that parse two string of second minute degre
        /// @param DMS_notation_1 one of the two coordinate
        /// @param DMS_notation_2 one of the two coordinate
        /// @note if any of the string is badly formated we throw an error Bad_format_Coordinate
        Sphere_Coordinate(std::string&& DMS_notation_1,std::string&& DMS_notation_2);
        double Get_Distance(const Sphere_Coordinate&) const; 
    private:
    double m_latitude;
    double m_longitude;
    static constexpr int earth_radius = 6339000; 
};

class Planar_Coordinate
{
    double x;
    double y;
    static double mean_x;
    static double mean_y;

    double operator>>(const Planar_Coordinate);
};

#endif //2D_COORDINATE_H