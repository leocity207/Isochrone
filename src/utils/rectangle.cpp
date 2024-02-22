#include "includes/utils/rectangle.h"


template<class T>
Utils::Rectangle<T>::Rectangle(T x_min, T x_max, T y_min, T y_max) :
	m_x_min(x_min),
	m_x_max(x_max),
	m_y_min(y_min),
	m_y_max(y_max)
{
}

template<class T>
T Utils::Rectangle<T>::Get_X_Length() const noexcept
{
	return m_x_max - m_x_min;
}

template<class T>
T Utils::Rectangle<T>::Get_Y_Length() const noexcept
{
	return m_y_max - m_y_min;
}

template<class T>
T Utils::Rectangle<T>::Get_X_Mean() const noexcept
{
	return (m_x_max + m_x_min)/2;
}

template<class T>
T Utils::Rectangle<T>::Get_Y_Mean() const noexcept
{
	return (m_y_max + m_y_min) / 2;
}

template<class T>
T Utils::Rectangle<T>::Get_X_Min() const noexcept
{
	return m_x_min;
}

template<class T>
T Utils::Rectangle<T>::Get_Y_Min() const noexcept
{
	return m_y_min;
}


template class Utils::Rectangle<size_t>;
template class Utils::Rectangle<int>;