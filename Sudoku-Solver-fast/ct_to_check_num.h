#pragma once

#include "board.h"
#include "from_internet.h"



template<size_t x, size_t y>
struct is_fixed {
	static constexpr bool val = global::board[x][y] > 0;
};

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

