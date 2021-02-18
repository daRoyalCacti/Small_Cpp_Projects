#pragma once
#include <array>

namespace global {
	constexpr std::array<std::array<double, 9>, 9> board =
	{
		std::array<double,9>{0, 0, 0, 8, 0, 1, 0, 0, 0},
		std::array<double,9>{0, 0, 0, 0, 0, 0, 0, 4, 3},
		std::array<double,9>{5, 0, 0, 0, 0, 0, 0, 0, 0},
		std::array<double,9>{0, 0, 0, 0, 7, 0, 8, 0, 0},
		std::array<double,9>{0, 0, 0, 0, 0, 0, 1, 0, 0},
		std::array<double,9>{0, 2, 0, 0, 3, 0, 0, 0, 0},
		std::array<double,9>{6, 0, 0, 0, 0, 0, 0, 7, 5},
		std::array<double,9>{0, 0, 3, 4, 0, 0, 0, 0, 0},
		std::array<double,9>{0, 0, 0, 2, 0, 0, 6, 0, 0}
	};

	std::array<std::array<double, 9>, 9> output_board = board;
};
