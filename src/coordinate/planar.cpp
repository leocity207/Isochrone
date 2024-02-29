#include "includes/coordinate/planar.h"
#include "includes/coordinate/sphere.h"
#include "includes/coordinate/projection.h"

#include<numbers>
#include<cmath>
#include <cassert>

template<class T>
Coordinate::Planar<T>::Planar(T x, T y) noexcept :
	Base<T>(x,y),
	m_x(this->first),
	m_y(this->second)
{

}

template<class T>
Coordinate::Planar<T>::Planar(const Coordinate::Spherical& , const Projection& ) noexcept :
	Base<T>(0,0),
	m_x(this->first),
	m_y(this->second)
{
	assert(false);
}

Coordinate::Planar<double>::Planar(const Coordinate::Spherical& sphere_coordinate,const Projection& projector) noexcept :
	Base<double>(projector.Project(sphere_coordinate)),
	m_x(this->first),
	m_y(this->second)
{

}

template<class T>
double Coordinate::Planar<T>::Distance_To(const Planar& other) const noexcept
{
	return std::sqrt((m_x - other.m_x) * (m_x - other.m_x) + (m_y - other.m_y) * (m_y - other.m_y));
}

template<class T>
T Coordinate::Planar<T>::Get_X() const noexcept
{
	return m_x;
}

template<class T>
T Coordinate::Planar<T>::Get_Y() const noexcept
{
	return m_y;
}


template class Coordinate::Planar<size_t>;

template class Coordinate::Planar<double>;

template class Coordinate::Planar<int>;