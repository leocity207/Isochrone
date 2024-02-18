#ifndef UTILS_SPHERE_COORDINATE_H
#define UTILS_SPHERE_COORDINATE_H

// STL
#include <string>


class Sphere_Coordinate
{
    ////////
    /// CTOR
    public:
        Sphere_Coordinate(double longitude,double latitude) noexcept;

        /////////////////////////////////////////////////////////////////////////////////////////
        /// @brief contructor that parse two string of second minute degre
        /// @param DMS_notation_1 one of the two coordinate
        /// @param DMS_notation_2 one of the two coordinate
        /// @note if any of the string is badly formated we throw an error Bad_format_Coordinate
        Sphere_Coordinate(const std::string_view& DMS_notation_1, const std::string_view& DMS_notation_2);

    ///////////
    /// METHODS
    public:
        double Get_Distance(const Sphere_Coordinate&) const; 
        const double& Get_Lattitude() const noexcept;
        const double& Get_Longitude() const noexcept;
        bool operator==(const Sphere_Coordinate& other_coord) const noexcept;

    //////////////
    /// ATTRIBUTES
    private:
        double m_latitude;
        double m_longitude;
    public:
        static constexpr int earth_radius = 6378100; 
};


#endif //UTILS_SPHERE_COORDINATE_H