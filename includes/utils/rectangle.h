#ifndef UTILS_RECTANGLE_H
#define UTILS_RECTANGLE_H

// Utils
#include "ctor.h"

namespace Utils
{
	template<class T>
	class Rectangle
	{
	////////
	/// CTOR
	public:
		DELETE_DEFAULT(Rectangle);
		Rectangle(T x_min, T x_max, T y_min, T y_max);

		T Get_X_Length() const noexcept;
		T Get_Y_Length() const noexcept;
		T Get_X_Mean() const noexcept;
		T Get_Y_Mean() const noexcept;
		T Get_X_Min() const noexcept;
		T Get_Y_Min() const noexcept;

	//////////////
	/// ATTRIBUTES
	private:
		T m_x_min;
		T m_x_max;
		T m_y_min;
		T m_y_max;
	};

	using Integer_Rectangle = Rectangle<size_t>;
}



#endif UTILS_RECTANGLE_H