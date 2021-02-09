//#include "Backtracking.h"
#include "compile_time.h"
#include <chrono>
#include <iostream>


template<int... Is>
void fU(const ints<Is...>& s)
{
	for (auto i : { Is... }) std::cout << i << " ";
	std::cout << "\n";
}





int main() {

	static_assert(board_valid::val, "board is not valid");

	constexpr xy test2{1,2};
	std::cout << test2.x<< " " << test2.y << "\n";

	
	constexpr std::array<int, 5> test = make_array_n<5>(89);
	for (const auto& a : test)
		std::cout << a << " ";
	std::cout << "\n";

	fU(left_to_check_y<3, 2>::val);

	const auto m = right_to_check_y<3, 2>::val;
	for (const auto& i : m)
		std::cout << i << " ";
	std::cout << "\n";

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
