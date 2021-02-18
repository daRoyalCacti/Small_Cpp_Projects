#pragma once

#include "ct_to_check.h"



template <typename T>
constexpr size_t i_to_x(const T i) {
	return i/9.0;	//will naturally floor function because return type is an integer type
}

template <typename T>
constexpr size_t i_to_y(const T i) {
	return i%9;
}


struct my_array {
	double* const* ptr;
	size_t num;
};



template <int... Is>
constexpr auto ct_to_rt_impl(const ints<Is...> s) {
	return std::array<my_array, sizeof...(Is)>{ my_array{&to_check_ptr<i_to_x(Is), i_to_y(Is)>::val[0],  to_check_ptr<i_to_x(Is), i_to_y(Is)>::val.size()} ...   };
}




auto ct_to_rt(const size_t x, const size_t y) {
	constexpr auto arr = ct_to_rt_impl(IS<80>());

	return arr[9*x+y];	
}

