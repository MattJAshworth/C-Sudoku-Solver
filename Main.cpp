/**
* Initial source code modified by MattJAshworth on 02/04/17.
* Final commit by MattJAshworth on 20/04/17.
* Updates at http://mattjamesashworth.com.
*/
#include "SudokuPuzzle.h"

using namespace std;
// This is a basic starting point for you to use to implement your Sudoku solver

int main(int argc, char **) {
	SudokuPuzzle puzzle;
	puzzle.Solve("sudoku_puzzle.txt");

	system("pause");



	return 0;
}


