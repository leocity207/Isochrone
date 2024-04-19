#ifndef GENERAL_H
#define GENERAL_H

// STL
#include <string_view>

////////////////////////////////////////////////////////////////////////////////////////
/// @brief Namesapce for general purpose function that could be used and reused anywhere
namespace Generals
{
	////////////////////////////////////////////////////////////////////
	/// @brief Trim spaces at the beginin and the end of a string
	/// @note If the string is void it return a void string.
	std::string_view Trim_Space_Front_Back(const std::string_view& str);
	std::string&& Trim_Space_Front_Back(std::string&& str);

	////////////////////////////////////////////////////
	/// @brief Parse an angular string of the form degre°minute'second' into its double representation
	/// @param str A string of the form degre°minute'second'
	/// @return The double value of the input string as a double
	/// @throw "ANGLE_BADLY_FORMATED" if the input string is not in the right format
	double Parse_Angle(const std::string_view& str);
}


#endif //GENERAL_H
