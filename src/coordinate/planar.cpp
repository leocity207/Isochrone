#include "includes/coordinate/planar.h"
#include "includes/coordinate/sphere.h"
#include "includes/coordinate/projector/base.h"

// STL
#include<cmath>

template<class T>
Coordinate::Planar<T>::Planar(T x, T y) noexcept :
	Base<T>(x,y)
{

}

template<class T>
template<class E>
Coordinate::Planar<T>::Planar(typename std::enable_if<Is_Float<T, E>(), const Spherical&>::type sphere_coordinate, const Coordinate::Projector::Base& projector) noexcept :
	Base<double>(projector.Project(sphere_coordinate))
{
}


template<class T>
double Coordinate::Planar<T>::Distance_To(const Planar& other) const noexcept
{
	return std::sqrt((X() - other.X()) * (X() - other.X()) + (Y() - other.Y()) * (Y() - other.Y()));
}

template<class T>
T Coordinate::Planar<T>::X() const noexcept
{
	return this->first;
}

template<class T>
T Coordinate::Planar<T>::Y() const noexcept
{
	return this->second;
}


template class Coordinate::Planar<size_t>;

template class Coordinate::Planar<double>;

template class Coordinate::Planar<int>;