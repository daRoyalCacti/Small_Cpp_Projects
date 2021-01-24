#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <array>
#include <numeric>
#include <functional>
#include <algorithm>

template <typename ... T>
std::vector<std::string> fill(const T& ... t) {
	std::vector<std::string> retval;
	std::stringstream ss;
	(void)std::initializer_list<int>{ (ss.str(""), ss << t, retval.push_back(ss.str()), 0)...};
	return retval;
}

template <typename T>
inline void print_vec(const T &vec) {
	for (const auto &v : vec) {
		std::cout << v << '\n';
	}
}


template <typename T>
inline void f(T a) {
	std::cout << a << '\n';
}


template <typename ...T>
inline void run_f(const T& ... t) {
	(void)std::initializer_list<int>{ (f(t), 0)... };
}


template<typename ... T>
std::vector<std::string> fill2(const T& ... t) {
	std::stringstream ss;
	return {(ss.str(""), ss << t, ss.str())... };
}



int main() {
	const auto v = fill("abc", 1, 5.4);
	print_vec(v);

	run_f("bca", 23, 3.423);

	print_vec(fill2("gac", 3432.34, 3));
}
