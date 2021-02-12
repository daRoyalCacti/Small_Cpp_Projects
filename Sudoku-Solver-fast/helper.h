#pragma once

#include "from_internet.h"


template <typename T, size_t a, size_t b, int... Is, int... Js> 
constexpr auto combine_arrays_t(const std::array<T, a> A, const ints<Is...>s, const std::array<T, b> B, const ints<Js...> t) {
	return std::array<T, a+b>{A[Is]..., B[Js]...};
}



template <typename T, size_t a, size_t b>
constexpr auto combine_arrays(const std::array<T, a> A, const std::array<T, b> B) {
	if constexpr (a == 0) {
		if constexpr (b==0) {
			return std::array<T, 0>{};
		} else {
			return B;
		}
	} else {
		if constexpr (b==0) {
			return A;
		} else {
			return combine_arrays_t(A, IS<a-1>(), B, IS<b-1>());
		}
	}
	
}	




template <typename T, size_t a, size_t b, size_t c>
constexpr auto combine_arrays(const std::array<T, a> A, const std::array<T, b> B, const std::array<T, c> C) {
	return combine_arrays(combine_arrays(A, B), C);
}	






template <typename T, typename U, size_t a, size_t b, int... Is, int... Js> 
constexpr auto combine_arrays_t(const std::array<T, a> A, const ints<Is...>s, const std::array<U, b> B, const ints<Js...> t) {
	return std::array<T, a+b>{A[Is]..., static_cast<T>(B[Js])...};
}



template <typename T, typename U, size_t a, size_t b>
constexpr auto combine_arrays(const std::array<T, a> A, const std::array<U, b> B) {
	if constexpr (a == 0) {
		if constexpr (b==0) {
			return std::array<T, 0>{};
		} else {
			return B;
		}
	} else {
		if constexpr (b==0) {
			return A;
		} else {
			return combine_arrays_t(A, IS<a-1>(), B, IS<b-1>());
		}
	}
	
}	




template <typename T, typename U, typename V, size_t a, size_t b, size_t c>
constexpr auto combine_arrays(const std::array<T, a> A, const std::array<U, b> B, const std::array<V, c> C) {
	return combine_arrays(combine_arrays(A, B), C);
}	
