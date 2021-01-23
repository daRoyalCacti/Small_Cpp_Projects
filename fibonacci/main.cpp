#include <iostream>
#include <utility>
#include <array>
#include <string>

typedef unsigned int_t;
constexpr unsigned max_fib_num = 46;

//for compile time evaluation of the Ith fibonacci number
template<int_t I>
struct Fib {
	static constexpr int_t val = Fib<I-1>::val + Fib<I-2>::val;
};

template<>
struct Fib<0> {
	static constexpr int_t val = 0;
};

template<>
struct Fib<1> {
	static constexpr int_t val = 1;
};


//for making the numbers accessable at runtime
template<size_t ... I>
int fib_impl(std::index_sequence<I...>, const size_t i) {
	constexpr std::array<int_t, sizeof...(I)> a = {Fib<I>::val...};

	return a[i];
}

int_t fib_run(const size_t i) {
	if (i==0) {return Fib<0>::val;}
	if (i==1) {return Fib<1>::val;}
	return fib_run(i-1) + fib_run(i-2);
}

int_t fib(const size_t i) {
	if (i <= max_fib_num) {
		return fib_impl(std::make_index_sequence<max_fib_num+1>(), i);
	} else {
		return fib_run(i);
	}
}



//https://www.math.net/list-of-fibonacci-numbers
int main(int argc, const char * argv[]) {
	if (argc > 1) {
		std::cout << "fibonacci number " << std::stoi(argv[1]) << " is "  <<  fib(std::stoi(argv[1])) << '\n';
	} else {
		std::cerr << "Requires 1 input argument" << std::endl;
	}

	return 0;
}
