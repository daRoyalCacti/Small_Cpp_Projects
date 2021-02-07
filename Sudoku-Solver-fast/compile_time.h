#pragma once
#include <array>

constexpr std::array<std::array<double, 9>, 9> board2 =
	{
		std::array<double,9>{0, 0, 0, 8, 0, 1, 0, 0, 0},
		std::array<double,9>{0, 0, 0, 0, 0, 0, 0, 4, 3},
		std::array<double,9>{5, 0, 0, 0, 0, 0, 0, 0, 0},
		std::array<double,9>{0, 0, 0, 0, 7, 0, 8, 0, 0},
		std::array<double,9>{0, 0, 0, 0, 0, 0, 1, 0, 0},
		std::array<double,9>{0, 2, 0, 0, 3, 0, 0, 0, 0},
		std::array<double,9>{6, 0, 0, 0, 0, 0, 0, 7, 5},
		std::array<double,9>{0, 0, 3, 4, 0, 0, 0, 0, 0},
		std::array<double,9>{0, 0, 0, 0, 0, 0, 6, 0, 0}
	};


//checking if 2 points have the same value
template <size_t x, size_t y, size_t i, size_t j>
struct equal {
	static constexpr bool val =(board2[x][y] != board2[i][j]);
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
	static constexpr bool val = colum_valid_t<x, y, counter-1>::val & (  (board2[counter][y] == 0) | (equalx<x, y, counter, y>::val) ) ;
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
	static constexpr bool val = row_valid_t<x, y, counter-1>::val & (  (board2[x][counter] == 0) | (equaly<x, y, x, counter>::val) ) ;
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
	static constexpr bool val = (x==boxx+h & y==boxy+counter) | short_row_t<x, y, h, counter-1>::val & (  (board2[boxx+h][boxy+counter] == 0) | (equal<x, y, boxx+h, boxy+counter>::val) )  ;

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

