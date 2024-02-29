#include "includes/coordinate/planar.h"
#include "includes/coordinate/sphere.h"
#include "includes/coordinate/projection.h"

#include<numbers>
#include<cmath>

template<class T>
Coordinate::Planar<T>::Planar(T x, T y) noexcept :
	Base<T>(x,y),
	m_x(this->first),
	m_y(this->second)
{

}

template<class T>
Coordinate::Planar<T>::Planar(const Coordinate::Spherical& sphere_coordinate,const Projection& projector) noexcept :
	Base<T>(projector.Project(sphere_coordinate)),
	m_x(this->first),
	m_y(this->second)
{

}

template<class T>
T Coordinate::Planar<T>::Distance_To(const Planar& other) const noexcept
{
	return std::sqrt((m_x - other.m_x) * (m_x - other.m_x) + (m_y - other.m_y) * (m_y - other.m_y));
}

template<class T>
T Coordinate::Planar<T>::Get_X() const noexcept
{
	return size_t();
}

template<class T>
T Coordinate::Planar<T>::Get_Y() const noexcept
{
	return size_t();
}
