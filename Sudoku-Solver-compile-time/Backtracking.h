#pragma once
#include <iostream>
#include <array>
#include "compile_time.h"

constexpr unsigned rows = 9;
constexpr unsigned cols = 9;
constexpr unsigned size = 81;





inline void print_board() { //prints the sudoku to console
	for (size_t j = 0; j < cols * 4; j++) std::cout << "-"; 
	std::cout << '\n'; //top line

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			if (j % 3 == 0) std::cout << "|  "; // vertical lines
			if (global::output_board[i][j] != 0) std::cout << static_cast<unsigned>(global::output_board[i][j]) << "  "; //the actual number
			else std::cout << "   "; //dont't print 0's - they are unsolved squares
		}
		std::cout << "|\n";
		if (i + 1 != rows && i % 3 != 2) for (size_t j = 0; j <= rows / 3; j++) std::cout << "|           "; // the vertical lines in linespacing
		std::cout << '\n';

		if (i % 3 == 2) { for (size_t j = 0; j < cols * 4; j++) std::cout << "-"; std::cout << std::endl; } //the horizontal lines

	}


}

template <typename U, typename V>
bool isValid(const U posx, const U posy, const V hor_box, const V vert_box) { //checks if the value in a given square is valid
	const auto arr = ct_to_rt(posx, posy);
	for (size_t i = 0; i < arr.num; i++)
		if (*arr.ptr[i] == global::output_board[posx][posy])
			return false;
	/*
	//col
	for (size_t i = 0; i < posy; i++) { //moving down
		if (board[posx][i] == board[posx][posy]) return false;
	}
	for (size_t i = posy + 1; i < cols; i++) { //moving down
		if (board[posx][i] == board[posx][posy]) return false;
	}

	//row
	for (size_t i = 0; i < posx; i++) { //moving left
		if (board[i][posy] == board[posx][posy]) return false;
	}
	for (size_t i = posx + 1; i < cols; i++) {
		if (board[i][posy] == board[posx][posy]) return false;
	}

	//is bad \/
	for (size_t i = hor_box ; i < hor_box + 3u; i++) {
		for (size_t j = vert_box; j < vert_box + 3u; j++) {
			if (i != posx && j != posy && board[i][j] == board[posx][posy]) return false;
		}
	}
	*/

	return true;
}

template <typename V>
void toSolve(V* solveArrayx, V* solveArrayy) { //creates an array of given numbers with some extra values for error checking
	
	solveArrayx[0] = size + 11; solveArrayy[0] = size+11;	//to know when the board is not solvable
	size_t counter = 1;
	//creating an array of given numbers
	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			//zero elements are what are being found
			if (global::board[i][j] == 0) {
				solveArrayx[counter] = i; solveArrayy[counter++] = j;
			}
		}
	}
	
	//known when finished when reach value that is outside the board
	solveArrayx[counter] = size+10; solveArrayy[counter] = size+10;
}

template <typename T>
void generateBox(T* hor_box, T* vert_box) {
	for (size_t i = 0; i < rows; i++) {
		hor_box[i] = static_cast<uint8_t>((i) / (float)rows * 3) * 3u;
	}

	for (size_t i = 0; i < cols; i++) {
		vert_box[i] = static_cast<uint8_t>((i) / (float)cols * 3) * 3u;
	}
}



void solve() { //solves the sudoku using backtracking

	unsigned solveArrayx[size+1], solveArrayy[size+1];
	toSolve(solveArrayx, solveArrayy);

	double hor_box[rows], vert_box[cols];
	generateBox(hor_box, vert_box);

	unsigned* ptrx = &solveArrayx[1], *ptry = &solveArrayy[1];


	while (*ptry <= cols + 1) {

		if (++global::output_board[*ptrx][*ptry] == 10) {
			global::output_board[*ptrx][*ptry] = 0;
			ptrx--;
			ptry--;

		}
		else 	if (isValid(*ptrx, *ptry, hor_box[*ptrx], vert_box[*ptry])) {
			ptrx++;
			ptry++;
		}

	}

	if (*ptry == size + 11 || *ptrx == size + 11)
		std::cerr << "no solution found" << std::endl;
}

