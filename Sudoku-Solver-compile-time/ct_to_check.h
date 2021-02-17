#pragma once

#include "board.h"
#include "from_internet.h"
#include "ct_to_check_num.h"
#include "helper.h"



template <size_t x, size_t counter>
struct next_fixed_row {
	static constexpr size_t val = is_fixed<x, counter>::val ? counter : next_fixed_row<x, counter+1>::val;
};


template <size_t x>
struct next_fixed_row<x, 9> {
	static constexpr size_t val = 5000;	//random value for debugging
};

template <size_t x, size_t y, size_t counter>
struct next_fixed_row_rec {
	static constexpr size_t val = next_fixed_row<x, next_fixed_row_rec<x, y, counter-1>::val+1>::val;
};

template <size_t x, size_t y>
struct next_fixed_row_rec<x, y, 0> {
	static constexpr size_t val = next_fixed_row<x, y>::val;
};



template <size_t x, size_t y, int... is>
constexpr auto right_to_check_y_t(const ints<is...> s) {
	return std::array<int, sizeof...(is)>{next_fixed_row_rec<x, y, is>::val...};
}


template <size_t x, size_t y>
struct right_to_check_y {	//assumes there is numbers to the right to check
	static constexpr auto val = right_to_check_y_t<x, y>(IS<num_check_right<x,y>::val-1>());	//val is std::array
};



template <int... is>
constexpr auto left_to_check_y_t(const ints<is...> s) {
	return std::array<int, sizeof...(is)>{is...};
}


template <size_t x, size_t y>
struct left_to_check_y {	//assumes there is numbers to the left to check
	static constexpr auto val = left_to_check_y_t(IS<y-1>());	//val is comma separed values (maybe??)
};


template <size_t x, size_t y>
constexpr auto row_to_check_y_t() {
	if constexpr (num_check_right<x,y>::val == 0) {
		if constexpr (y == 0) {
			return std::array<int, 0>{};
		} else {
			return left_to_check_y<x,y>::val;
		}
	} else if constexpr (y==0) {
		return right_to_check_y<x,y>::val;
	} else {
		return combine_arrays(left_to_check_y<x, y>::val, right_to_check_y<x, y>::val);
	}
}

template <size_t x, size_t y>
struct row_to_check_y {
	static constexpr auto val = row_to_check_y_t<x,y>();
};


template <size_t x, size_t y>
struct row_to_check_x {
	static constexpr auto val = make_array_n<num_check_row<x,y>::val>(x);
};


















template <size_t y, size_t counter>
struct next_fixed_col {
	static constexpr size_t val = is_fixed<counter, y>::val ? counter : next_fixed_col<y, counter+1>::val;
};


template <size_t y>
struct next_fixed_col<y, 9> {
	static constexpr size_t val = 5000;	//random value for debugging
};

template <size_t x, size_t y, size_t counter>
struct next_fixed_col_rec {
	static constexpr size_t val = next_fixed_col<y, next_fixed_col_rec<x, y, counter-1>::val+1>::val;
};

template <size_t x, size_t y>
struct next_fixed_col_rec<x, y, 0> {
	static constexpr size_t val = next_fixed_col<y, x>::val;
};



template <size_t x, size_t y, int... is>
constexpr auto down_to_check_x_t(const ints<is...> s) {
	return std::array<int, sizeof...(is)>{next_fixed_col_rec<x, y, is>::val...};
}


template <size_t x, size_t y>
struct down_to_check_x {	//assumes there is numbers to the right to check
	static constexpr auto val = down_to_check_x_t<x, y>(IS<num_check_down<x,y>::val-1>());	//val is std::array
};



template <int... is>
constexpr auto up_to_check_x_t(const ints<is...> s) {
	return std::array<int, sizeof...(is)>{is...};
}


template <size_t x, size_t y>
struct up_to_check_x {	//assumes there is numbers to the left to check
	static constexpr auto val = up_to_check_x_t(IS<x-1>());	
};



template <size_t x, size_t y>
constexpr auto col_to_check_x_t() {
	if constexpr (num_check_down<x,y>::val == 0) {
		if constexpr (x == 0) {
			return std::array<int, 0>{};
		} else {
			return up_to_check_x<x,y>::val;
		}
	} else if constexpr (x==0) {
		return down_to_check_x<x,y>::val;
	} else {
		return combine_arrays(up_to_check_x<x, y>::val, down_to_check_x<x, y>::val);
	}
}


template <size_t x, size_t y>
struct col_to_check_x {
	static constexpr auto val = col_to_check_x_t<x, y>();
};


template <size_t x, size_t y>
struct col_to_check_y {
	static constexpr auto val = make_array_n<num_check_col<x,y>::val>(y);
};




template <size_t x, size_t y, size_t col>
constexpr auto check_box_col_x_t() {
	constexpr auto boxx = box<x>::val;
	constexpr auto boxy = box<y>::val;

	constexpr size_t cy = boxy + col;

	if constexpr (y == cy) {
		return std::array<int, 0>{};
	} else 	{

		constexpr size_t diff = x - boxx;

		if constexpr (diff == 0) {

			if constexpr (!is_fixed<boxx+1, cy>::val) {
				if constexpr (!is_fixed<boxx+2,cy>::val) {
					return std::array<int, 0>{};
				} else {
					return std::array<int, 1>{boxx+2};
				}
			} else {
				if constexpr (!is_fixed<boxx+2, cy>::val) {
					return std::array<int, 1>{boxx+1};
				} else {
					return std::array<int, 2>{boxx+1, boxx+2};
				}
			}

		} else if constexpr (diff == 1) {
			if constexpr (!is_fixed<boxx+2,cy>::val) {
				return std::array<int, 1>{boxx};
			} else {
				return std::array<int, 2>{boxx, boxx+2};
			}
		} else {
			return std::array<int, 2>{boxx, boxx+1};
		}
	}
}


template <size_t x, size_t y>
struct box_to_check_x {
	static constexpr auto val = combine_arrays(check_box_col_x_t<x, y, 0>(), check_box_col_x_t<x, y, 1>(), check_box_col_x_t<x, y, 2>());
};


template <size_t x, size_t y>
struct box_to_check_y {
private:
	static constexpr auto boxy = box<y>::val;
public:
	static constexpr auto val = combine_arrays( make_array_n<check_box_col_x_t<x,y,0>().size()>(boxy)  ,  
			make_array_n<check_box_col_x_t<x,y,1>().size()>(boxy+1)  ,  
			make_array_n<check_box_col_x_t<x,y,2>().size()>(boxy+2) );
};







template<size_t x, size_t y>
struct to_check_x {
	static constexpr auto val = combine_arrays(row_to_check_x<x, y>::val, col_to_check_x<x, y>::val, box_to_check_x<x,y>::val);
};


template<size_t x, size_t y>
struct to_check_y {
	static constexpr auto val = combine_arrays(row_to_check_y<x, y>::val, col_to_check_y<x, y>::val, box_to_check_y<x,y>::val);
};


template <size_t x, size_t y, int...Is>
constexpr auto to_check_ptr_impl(const ints<Is...> s) {
	constexpr auto xs = to_check_x<x,y>::val;
	constexpr auto ys = to_check_y<x,y>::val;
	return std::array<double*, sizeof...(Is)>{&global::output_board[xs[Is]][ys[Is]]...};
};


template<size_t x, size_t y>
struct to_check_ptr {
	static_assert(to_check_x<x,y>::val.size() == to_check_y<x,y>::val.size(), "x and y must have same number of elements");
	static constexpr auto val = to_check_ptr_impl<x, y>(IS<to_check_x<x,y>::val.size()-1>());
};
