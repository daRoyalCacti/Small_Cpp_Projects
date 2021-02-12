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
