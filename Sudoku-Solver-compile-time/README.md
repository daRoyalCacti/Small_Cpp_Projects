# Sudoku solver (with compile time calculations)
This was mainly just an exercise in compile time programming. This Sudoku solver is slower than its runtime equivilent.

During the solving of the sudoku, a very common computation is checking if a value in a given square is valid. The runtime version checked all of the 'blank squares' (the squares that were still to be solved). This programs finds what squares need to be checked at compile time for the runtime algorithm to use. This greatly reduced the number of comparisions, however it greatly increased the number of memory access. This is likely the main cause of the slow down.
