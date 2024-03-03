#ifndef COORDINATE_PLANAR_H
#define COORDINATE_PLANAR_H

#include "coordinate.h"


namespace Coordinate
{
    namespace Projector { class Base; };
    class Spherical;

    template<class T, class E>
    constexpr bool Is_Float()
    {
        return std::is_same< E, const Spherical&>::value&& std::is_floating_point<T>::value;
    }


    template<class T>
    class Planar : public Base<T>
    {
        ////////
        /// CTOR
    public:
        DELETE_DEFAULT_CTOR(Planar)
        DEFAULT_MOVE(Planar)
        DEFAULT_COPY(Planar)
        Planar(T x,T y) noexcept;

        //////////////////////////////////////////////////////////
        /// This construcor is only enabled if T is floating point
        template<class E>
        Planar(typename std::enable_if<Is_Float<T,E>(), const Spherical&>::type sphere_coordinate, const Coordinate::Projector::Base& projector) noexcept;


        ///////////
        /// METHODS
    public:
        double Distance_To(const Planar&) const noexcept;
        T X() const noexcept;
        T Y() const noexcept;
    };
}
#endif //COORDINATE_PLANAR_H