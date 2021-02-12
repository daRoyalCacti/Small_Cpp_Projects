#pragma once

#include "from_internet.h"


template <typename T, size_t a, size_t b, int... Is, int... Js> 
constexpr auto combine_arrays_t(const std::array<T, a> A, const ints<Is...>s, const std::array<T, b> B, const ints<Js...> t) {
	return std::array<T, a+b>{A[Is]..., B[Js]...};
}



template <typename T, size_t a, size_t b>
constexpr auto combine_arrays(const std::array<T, a> A, const std::array<T, b> B) {
	return combine_arrays_t(A, IS<a-1>(), B, IS<b-1>());
}	
