
#include <variant>

#include <boost/variant.hpp>


#include <boost/mpl/vector.hpp>

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/mpl/for_each.hpp>
#include <typeinfo>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/mpl.hpp>


namespace bmpl = boost::mpl;
namespace bf = boost::fusion;





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
constexpr auto ct_to_rt_impl(const ints<Is...> s, const ints<Js...> p) {
	constexpr auto uniq_size = get_unique_sizes();
	constexpr auto arr = array_sizes();

	typedef std::variant<std::array<double*, arr[uniq_size[Js]]>...> a;
	
	constexpr std::array<a, sizeof...(Is)> ret_stuff{ to_check_ptr<i_to_x(Is), i_to_y(Is)>::val... };

	/*typedef bmpl::vector<std::array<double*, arr[uniq_size[Js]]>...> array_collection;
	constexpr typename bf::result_of::as_vector<array_collection>::type arrays( to_check_ptr<i_to_x(Is), i_to_y(Is)>::val... );*/
	//constexpr boost::fusion::vector<std::array<double*, arr[Is]>...> arrays{to_check_ptr<i_to_x(Is), i_to_y(Is)>::val... };
 
	//double test = 4;
	//double* test2 = &test;
	//bf::at_c<0>(arrays) = {test2, test2, test2, test2};

	return ret_val;
}




auto ct_to_rt(const size_t x, const size_t y) {
	constexpr auto arr = ct_to_rt_impl(IS<80>(), IS<num_unique(array_sizes())-1>());

	//return arr(x*9+y);
	return arr[x*9+y];
	
	//constexpr auto arr2 = array_sizes();
	//return std::get<  std::array<double*, arr2[x*9+y]>  >(arr[x*9+y]);
}
