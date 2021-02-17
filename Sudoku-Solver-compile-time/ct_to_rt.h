#pragma once

#include "ct_to_check.h"

#include <variant>

//#include <boost/variant.hpp>

/*
#include <boost/mpl/vector.hpp>

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/mpl/for_each.hpp>
#include <typeinfo>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/mpl.hpp>


namespace bmpl = boost::mpl;
namespace bf = boost::fusion;
*/

template <typename T>
constexpr size_t i_to_x(const T i) {
	return i/9.0;	//will naturally floor function because return type is an integer type
}

template <typename T>
constexpr size_t i_to_y(const T i) {
	return i%9;
}



template <int... Is>
constexpr auto array_sizes_impl(const ints<Is...> s) {
	return std::array<size_t, sizeof...(Is)>{to_check_x<i_to_x(Is), i_to_y(Is)>::val.size()...};
}

constexpr std::array<size_t, 81> array_sizes() {
	return array_sizes_impl(IS<80>());
}


template <int counter, typename T>
constexpr bool is_first_occurance_impl(const T &arr, const size_t to_check) {
	if constexpr (counter < 0) {
		return true;
	} else if constexpr (counter == 0) {
		return arr[to_check] != arr[counter];
	} else {
		return (arr[to_check] != arr[counter]) && is_first_occurance_impl<counter-1>(arr, to_check)  ;
	}
}


template <int to_check, typename T>
constexpr bool is_first_occurance(const T &arr) {
	return is_first_occurance_impl<to_check-1>(arr, to_check);
}



template <int to_check_c, typename T> 
constexpr size_t num_unique_impl(const T &arr)  {
	if constexpr (to_check_c < 0) {
		return 0;
	} else if constexpr (to_check_c == 0) {
		return 1;
	} else {
		return is_first_occurance<to_check_c>(arr) + num_unique_impl<to_check_c-1>(arr);
	}
};

template <typename T, size_t x>
constexpr size_t num_unique(const std::array<T, x> &arr) {
	return num_unique_impl<x-1>(arr);
}


template <size_t start>
constexpr size_t get_next_unique() {
	constexpr auto arr = array_sizes();
	if constexpr (is_first_occurance<start>(arr)) {
		return start;
	} else {
		return get_next_unique<start+1>();
	}
}


template <size_t start>
constexpr size_t get_next_unique_rec() {
	if constexpr (start == 0) {
		return 0;
	} else {
		return get_next_unique< get_next_unique_rec<start-1>() + 1>();
	}
}


template <int...Is>
constexpr auto get_unique_ids_impl(const ints<Is...> s) {
	return std::array<size_t, sizeof...(Is)>{get_next_unique_rec<Is>()...};
}


constexpr auto get_unique_sizes() {
	constexpr auto arr = array_sizes();
	return get_unique_ids_impl(  IS<num_unique(arr)-1>()  );
}


template <int... Is, int... Js>
auto ct_to_rt_impl(const size_t x, const size_t y, const ints<Is...> s, const ints<Js...> p) {
	//typedef std::variant<double, float, int, std::array<double, 3>> a;
	//typedef std::variant<decltype(Is)...> a;

	
	//return get_unique_sizes();

	/*
	typedef std::variant<std::array<double, 4>, std::array<double, 5>> a;
	const auto v = std::array<double, 4>{12.4, 5643, 54, 564};

	std::array<a, 2> vasd{std::array<double, 5>{12, 3424, 436, 35, 543}, v};


	typedef std::variant<int, int> q;
	std::array<q, 7> af{1, 3, 675, 5432, 234, 423, 5234};
	*/


	constexpr auto uniq_size = get_unique_sizes();
	constexpr auto arr = array_sizes();

	typedef std::variant<std::array<double*, arr[uniq_size[Js]]>...> a;
	

	constexpr std::array<a, sizeof...(Is)> ret_stuff{ to_check_ptr<i_to_x(Is), i_to_y(Is)>::val... };

	return ret_stuff;
	

	//typedef boost::variant<std::array<double*, to_check_x<i_to_x(Is), i_to_y(Is)>::val.size()>...> array_collection;
	//std::array<boost::variant<std::array<double*, to_check_x<i_to_x(Is), i_to_y(Is)>::val.size()>...>, 2> array_collection;

	//std::array<array_collection, sizeof...(Is)> a;
	//typedef boost::variant<int, double, int, std::array<double, 4>> array_collection;
	//
	//typedef boost::variant<decltype(Is)...> array_collection;
	//typedef boost::variant<std::array<double*, to_check_x<i_to_x(Is), i_to_y(Is)>::val.size()>...> array_collection;
	//
	//array_collection asdf;
	/*array_collection asdf;
	asdf = 4;
	array_collection  fda;
	fda = std::array<double, 4>{1,3,4,5};*/
}

/*
//https://stackoverflow.com/questions/3348936/array-of-arrays-of-different-size
template <int... Is>
auto ct_to_rt_impl(const size_t x, const size_t y, const ints<Is...> s) {
	//typedef bmpl::vector<std::array<double*, to_check_x<i_to_x(Is), i_to_y(Is)>::val.size()>...> array_collection;
	
	typedef bmpl::vector<std::array<double, Is>...> afsda;
	const auto a = std::array<int, sizeof...(Is)>{Is...};
	//typedef bmpl::vector<double, int, float, std::array<double,3>> array_collection;

	const size_t i = x*9+y;

	//array_collection asdf;
	//test(asdf);
	
	//typedef  bf::result_of::as_vector<array_collection>::type array_fusion;
	
	//const array_fusion arrays;
	//array_fusion arrays{ to_check_ptr<i_to_x(Is), i_to_y(Is)>::val... };
	
};
*/

/*
template <typename T>
void test(T x) {
	//typename bf::result_of::as_vector<T>::type array_fusion p = void;

}
*/


//not actually what i want
auto ct_to_rt(const size_t x, const size_t y) {
	return ct_to_rt_impl(x, y, IS<80>(), IS<num_unique(array_sizes())-1>());
}
