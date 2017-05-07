#pragma once

#include <iostream>
#include <fstream>
#include "Blocks.h"
using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);
	

	//Archived
	void Read(char filenameIn[]);
	int Grid[9][9];
	struct CellObject {
		int Value; //The value of the object
		bool preDefined;
		int candidateList[0];
	};
	//End of Archive



private:
	void Output() const;

	void ReadToGrid(char filenameIn[]);
	bool NarrowCandidates(CellObj* checkCell, int row, int col, int checkBlock);
	bool CheckNakedSingle(CellObj* checkCell, int block, int row, int col);
	bool CheckHiddenSingle(CellObj* checkCell, int row, int col, int block, int index);
	bool IsIn(const Blocks &cellGroup, int currentCell, int value);
	void InitSolve();

	MetaLog meta;
	Blocks gridBlocks[9];
	Blocks gridRows[9];
	Blocks gridColumns[9];
};

