#ifndef GENERAL_HPP
#define GENERAL_HPP

// STL
#include <type_traits>
#include <ranges>

// General
#include "general.h"
#include "exception_def.h"

template<class T>
std::vector<std::vector<T>> Generals::Transpose(const std::vector<std::vector<T>>& matrix)
{
	static_assert(std::is_copy_assignable<T>::value, "T need to be swappable");

    if (matrix.empty() || matrix[0].empty())
        THROW(SIZE_IS_ZERO)

    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    for (const auto& row : matrix)
        if (row.size() != cols)
            THROW(NOT_RECTANGULAR)

    std::vector<std::vector<T>> result(cols, std::vector<T>(rows));

    for (size_t j : std::views::iota(0u, cols))
        for (size_t i : std::views::iota(0u, rows))
            result[j][i] = matrix[i][j];

    return result;
}



#endif //GENERAL_HPP
