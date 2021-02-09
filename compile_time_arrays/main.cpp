#include <iostream>
#include <array>


//https://ngathanasiou.wordpress.com/2015/02/19/compile-time-integer-sequences/
// a sequence container -------------------------
template<int ...>
struct ints 
{ 
};
// integer sequence -----------------------------
template<int N, int... Is>
struct int_seq : int_seq<N - 1, N, Is...> 
{ 
};

template<int... Is>
struct int_seq<0, Is...> 
{
	using type = ints<0, Is...>;
};
// convenience alias -----------------------------
template<int N>
using IS = typename int_seq<N>::type; 






constexpr std::array<int, 7> a = {-2, 4, -16, 12, -5, 5, 15};
constexpr size_t num = 4;	//have way to figure out

template <int x>
struct above_zero {
	static constexpr bool val = x > 0;
};

template <size_t counter>
struct return_bigger {
	static constexpr int val = a[counter] > 0 ? counter : return_bigger<counter+1>::val;
};

template <>
struct return_bigger<a.size()> {
	static constexpr int val = -2;
};


template<size_t i>
struct return_bigger_rec {
	static constexpr int val = return_bigger<return_bigger_rec<i-1>::val+1>::val;
};

template<>
struct return_bigger_rec<0> {
	static constexpr int val = return_bigger<0>::val;
};


template <size_t ... I>
constexpr std::array<int, num> want_impl(std::index_sequence<I...>) {
	constexpr std::array<int, sizeof...(I)> a = {return_bigger_rec<I>::val...};
	return a;
}



template <int... Is>
constexpr auto foo(const ints<Is...> s) {
	const std::array<int, sizeof...(Is)> temp = {return_bigger_rec<Is>::val...};
	return temp;
}


int main() {
	constexpr auto p = foo(IS<num-1>());

	for (const auto& b : p)
		std::cout << b << "\n";
	return 0;
}

