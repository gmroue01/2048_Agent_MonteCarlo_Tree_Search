#pragma once
#include <array>


inline constexpr int N = 4;

using Grid = std::array<std::array<int,N>,N>;


void display(const Grid& grid);






