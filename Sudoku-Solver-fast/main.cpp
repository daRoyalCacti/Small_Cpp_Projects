//#include "Backtracking.h"
#include "compile_time.h"
#include <chrono>
#include <iostream>

std::array<std::array<double, 9>, 9> output_board{};

std::array<std::array<double, 9>, 9> board =
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

int main() {

	//std::cout << board_valid(board2);	
	std::cout << point_valid<7, 3>::val << "\n";
	std::cout << colum_valid<7,3>::val << "\n";
	std::cout << row_valid<7,3>::val << "\n";
	std::cout << box_valid<7,3>::val << "\n";


/*
	std::cout << "Board to solve" << std::endl;
	print_board(board);

	if (!boardValid(board)) {
		std::cerr << "Board is not valid" << std::endl;
		return 1;
	}

	std::cout << "Solving..." << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	solve(board, output_board);
	auto end = std::chrono::high_resolution_clock::now();
	double time = std::chrono::duration <double, std::milli>(end - start).count();


	std::cout << "\nSolved board" << std::endl;
	print_board(board);


	std::cout.precision(5);
	if (time < 1000)
		std::cout << "\nBoard solved in " << time << "ms" << std::endl;
	else if (time < 60000) {
		time /= 1000;
		std::cout << "\nBoard solved in " << time << "s" << std::endl;
	}
	else {
		time /= 60000;
		std::cout << "\nBoard solved in " << time << "min" << std::endl;
	}

#ifdef _WIN32
	getchar();
#endif
*/
	return 0;
}
