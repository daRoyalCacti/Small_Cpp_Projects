#include "Backtracking.h"
#include <chrono>
#include <iostream>

#include "compile_time.h"

constexpr size_t tx = 2;
constexpr size_t ty = 4; 



int main() {



/*	
	const auto l = to_check_y<tx, ty>::val;
	for (const auto& i : l)
		std::cout << i << " ";
	std::cout << "\n";

	const auto m = to_check_x<tx, ty>::val;
	for (const auto& i : m)
		std::cout << i << " ";
	std::cout << "\n\n";


	

	const auto b = ct_to_rt(0, 0);
	for (size_t i = 0; i < b.num; i++)
		std::cout << *b.ptr[i] << ' ';
	std::cout << '\n';
*/





	static_assert(board_valid::val, "board is not valid");

	std::cout << "Board to solve" << std::endl;
	print_board();


	

	std::cout << "Solving..." << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	solve();
	auto end = std::chrono::high_resolution_clock::now();
	double time = std::chrono::duration <double, std::milli>(end - start).count();


	std::cout << "\nSolved board" << std::endl;
	print_board();


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

	return 0;
}
