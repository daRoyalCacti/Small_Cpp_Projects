//#include "Backtracking.h"
#include "compile_time.h"
#include <chrono>
#include <iostream>




int main() {

	//std::cout << board_valid(board2);	

	
	//std::cout << board_valid::val << "\n";
	static_assert(board_valid::val, "board is not valid");

	
	std::cout << num_check_box<0,0>::val << "\n";
	std::cout << num_check_box<0,6>::val << "\n";
	std::cout << num_check_box<2,4>::val << "\n";
	std::cout << num_check_box<5,0>::val << "\n";
	std::cout << num_check_box<5,4>::val << "\n";
	



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
