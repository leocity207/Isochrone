#ifndef COORDINATE_PLANAR_H
#define COORDINATE_PLANAR_H

#include "coordinate.h"


namespace Coordinate
{
    class Projection;
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
        DELETE_COPY(Planar)
        Planar(T x,T y) noexcept;

        //////////////////////////////////////////////////////////
        /// This construcor is only enabled if T is floating point
        template<class E>
        Planar(typename std::enable_if<Is_Float<T,E>(), const Spherical&>::type sphere_coordinate, const Projection& projector) noexcept;


        ///////////
        /// METHODS
    public:
        double Distance_To(const Planar&) const noexcept;
        T Get_X() const noexcept;
        T Get_Y() const noexcept;

        //////////////
        /// ATTRIBTUES
    private:
        T& m_x;
        T& m_y;
    };
}
#endif //COORDINATE_PLANAR_H