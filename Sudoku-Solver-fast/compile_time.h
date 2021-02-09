#pragma once
#include "board.h"


//checking if 2 points have the same value
template <size_t x, size_t y, size_t i, size_t j>
struct equal {
	static constexpr bool val =(global::board[x][y] != global::board[i][j]);
};

template <size_t x, size_t y, size_t i, size_t j>
struct equalx {
	static constexpr bool val = x==i | equal<x,y,i,j>::val;
};

template <size_t x, size_t y, size_t i, size_t j>
struct equaly {
	static constexpr bool val = y==j | equal<x,y,i,j>::val;
};






template<size_t x, size_t y, int counter>
struct colum_valid_t {
	static constexpr bool val = colum_valid_t<x, y, counter-1>::val & (  (global::board[counter][y] == 0) | (equalx<x, y, counter, y>::val) ) ;
};

template<size_t x, size_t y>
struct colum_valid_t<x,y, -1> {
	static constexpr bool val = true;
};

template<size_t x, size_t y>
struct colum_valid {
	static constexpr bool val = colum_valid_t<x,y,8>::val;
};







template<size_t x, size_t y, int counter>
struct row_valid_t {
	static constexpr bool val = row_valid_t<x, y, counter-1>::val & (  (global::board[x][counter] == 0) | (equaly<x, y, x, counter>::val) ) ;
};

template<size_t x, size_t y>
struct row_valid_t<x,y, -1> {
	static constexpr bool val = true;
};

template<size_t x, size_t y>
struct row_valid {
	static constexpr bool val = row_valid_t<x,y,8>::val;
};


//works for both x and y
template<size_t x>
struct box {
	static constexpr unsigned val = static_cast<unsigned>(x/3.0)*3;
};







template<size_t x, size_t y, size_t h, int counter>
struct short_row_t {
private:
	static constexpr unsigned boxx = box<x>::val;
	static constexpr unsigned boxy = box<y>::val;
public:
	static constexpr bool val = (x==boxx+h & y==boxy+counter) | short_row_t<x, y, h, counter-1>::val & (  (global::board[boxx+h][boxy+counter] == 0) | (equal<x, y, boxx+h, boxy+counter>::val) )  ;

};

template<size_t x, size_t y, size_t h>
struct short_row_t<x,y,h, -1> {
	static constexpr bool val = true;
};


template<size_t x, size_t y>
struct box_valid {
	static constexpr bool val = short_row_t<x, y, 0, 2>::val & short_row_t<x, y, 1, 2>::val & short_row_t<x, y, 2, 2>::val;
};






template<size_t x, size_t y>
struct point_valid {
	static constexpr bool val = box_valid<x,y>::val & row_valid<x,y>::val & colum_valid<x,y>::val;
};


template<size_t x, size_t y>
struct board_valid_t {
	static constexpr bool val = point_valid<x, y>::val & board_valid_t<x+1, y>::val & board_valid_t<x, y+1>::val;
};

template<>
struct board_valid_t<9, 9> {
	static constexpr bool val = true;
};

template<size_t x>
struct board_valid_t<x, 9> {
	static constexpr bool val = true;
};

template<size_t y>
struct board_valid_t<9, y> {
	static constexpr bool val = true;
};


struct board_valid {
	static constexpr bool val = board_valid_t<0,0>::val;
};




template<size_t x, size_t y>
struct is_fixed {
	static constexpr bool val = global::board[x][y] > 0;
};











//generating an integer sequence starting from 0 at compile time
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
using IS = typename int_seq<N>::type; 	//IS := integer sequence
//IS<4> returns 0,1,2,3,4



//generating an array full of a constant value
//https://stackoverflow.com/questions/1065774/initialization-of-all-elements-of-an-array-to-one-default-value-in-c
template<std::size_t size, typename T, std::size_t... indexes>
constexpr auto make_array_n_impl(T && value, std::index_sequence<indexes...>) {
    // Use the comma operator to expand the variadic pack
    // Move the last element in if possible. Order of evaluation is well-defined
    // for aggregate initialization, so there is no risk of copy-after-move
    return std::array<std::decay_t<T>, size>{ (static_cast<void>(indexes), value)..., std::forward<T>(value) };
}



template<typename T>
constexpr auto make_array_n(std::integral_constant<std::size_t, 0>, T &&) {
    return std::array<std::decay_t<T>, 0>{};
}

template<std::size_t size, typename T>
constexpr auto make_array_n(std::integral_constant<std::size_t, size>, T && value) {
    return make_array_n_impl<size>(std::forward<T>(value), std::make_index_sequence<size - 1>{});
}


template<std::size_t size, typename T>
constexpr auto make_array_n(T && value) {
    return make_array_n(std::integral_constant<std::size_t, size>{}, std::forward<T>(value));
}
//make_array_n<5>(2) returns {2,2,2,2,2}




template <size_t x, size_t y>
struct num_check_right_t {
	static constexpr size_t val = is_fixed<x, y>::val + num_check_right_t<x, y+1>::val;
};

template <size_t x>
struct num_check_right_t<x, 9> {
	static constexpr size_t val = 0;
};

template<size_t x, size_t y>
struct num_check_right {
	static constexpr size_t val = num_check_right_t<x, y+1>::val;
};


template <size_t x, size_t y>
struct num_check_row {
	static constexpr size_t val = y + num_check_right<x, y>::val; 	//always have all numbers to the left plus any extras to the right 	
};





template <size_t x, size_t y>
struct num_check_down_t {
	static constexpr size_t val = is_fixed<x, y>::val + num_check_down_t<x+1, y>::val;
};

template <size_t y>
struct num_check_down_t<9, y> {
	static constexpr size_t val = 0;
};

template<size_t x, size_t y>
struct num_check_down {
	static constexpr size_t val = num_check_down_t<x+1, y>::val;
};


template <size_t x, size_t y>
struct num_check_col {
	static constexpr size_t val = x + num_check_down<x, y>::val; 	//always have all numbers to the left plus any extras to the right 	
};



template <size_t x, size_t y>
struct num_check_box {
private:
	static constexpr unsigned boxx = box<x>::val;
	static constexpr unsigned boxy = box<y>::val;

	static constexpr size_t aa = is_fixed<boxx  ,boxy  >::val & !(boxx   == x & boxy   == y  );
	static constexpr size_t ab = is_fixed<boxx  ,boxy+1>::val & !(boxx   == x & boxy+1 == y  );
	static constexpr size_t ac = is_fixed<boxx  ,boxy+2>::val & !(boxx   == x & boxy+2 == y  );
	static constexpr size_t ba = is_fixed<boxx+1,boxy  >::val & !(boxx+1 == x & boxy   == y  );
	static constexpr size_t bb = is_fixed<boxx+1,boxy+1>::val & !(boxx+1 == x & boxy   == y+1);
	static constexpr size_t bc = is_fixed<boxx+1,boxy+2>::val & !(boxx+1 == x & boxy   == y+2);
	static constexpr size_t ca = is_fixed<boxx+2,boxy  >::val & !(boxx+2 == x & boxy   == y  );
	static constexpr size_t cb = is_fixed<boxx+2,boxy+1>::val & !(boxx+2 == x & boxy   == y+1);
	static constexpr size_t cc = is_fixed<boxx+2,boxy+2>::val & !(boxx+2 == x & boxy   == y+2);
		
public:
	static constexpr size_t val =  aa + ab+ ac+ ba+ bb+ bc+ ca+ cb+ cc;
};


template <size_t x, size_t y>
struct num_check {
	static constexpr size_t val = num_check_box<x, y>::val + num_check_col<x,y>::val + num_check_row<x,y>::val;
};




template <typename T>
struct xy {
	T x;
	T y;
};

/*
template <size_t x, size_t y>
constexpr auto create_xy_row() {

	const std::array<int, num_check<x,y>::val> = {
}
*/


template <size_t x, size_t counter>
struct next_fixed {
	static constexpr size_t val = is_fixed<x, counter>::val ? counter : next_fixed<x, counter+1>::val;
};


template <size_t x>
struct next_fixed<x, 9> {
	static constexpr size_t val = -2;	//random value for debugging
};

template <size_t x, size_t y, size_t counter>
struct next_fixed_rec {
	static constexpr size_t val = next_fixed<x, next_fixed_rec<x, y, counter-1>::val+1>::val;
};

template <size_t x, size_t y>
struct next_fixed_rec<x, y, 0> {
	static constexpr size_t val = next_fixed<x, y>::val;
};



template <size_t x, size_t y, int... Is>
constexpr auto right_to_check_y_t(const ints<Is...> s) {
	return std::array<int, sizeof...(Is)>{next_fixed_rec<x, y, Is>::val...};
}


template <size_t x, size_t y>
struct right_to_check_y {	//assumes there is numbers to the right to check
	static constexpr auto val = right_to_check_y_t<x, y>(IS<num_check_right<x,y>::val-1>());	//val is std::array
};



template <size_t x, size_t y>
struct left_to_check_y {	//assumes there is numbers to the left to check
	static constexpr auto val = IS<y-1>();	//val is comma separed values (maybe??)
};



