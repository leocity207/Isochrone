#include "includes/coordinate/coordinate.h"

#include <vector>


template<class T>
Coordinate::Base<T>::Base(T first, T second):
	std::pair<T,T>(first, second)
{
}

template<class T>
Coordinate::Base<T>& Coordinate::Base<T>::operator+=(const Coordinate::Base<T>& other)
{
	this->first += other.first;
	this->second += other.second;
	return *this;
}

template<class T>
template<class E>
Coordinate::Base<T>& Coordinate::Base<T>::operator/=(E constant)
{
	static_assert(std::is_scalar<E>::value, "coordinate should be made of scalar type");
	this->first /= (T)constant;
	this->second /= (T)constant;
	return *this;
}

template<class T>
Coordinate::Base<T> Coordinate::Base<T>::Compute_Mean(std::vector<std::reference_wrapper<const Coordinate::Base<T>>> & coordinates) noexcept
{
	Coordinate::Base<T> mean_coordiante;
	for (const Base<T>& coordinate : coordinates)
		mean_coordiante += coordinate;
	mean_coordiante /= coordinates.size();
	return mean_coordiante;
}


template class Coordinate::Base<size_t>;

template class Coordinate::Base<double>;

template class Coordinate::Base<int>;
