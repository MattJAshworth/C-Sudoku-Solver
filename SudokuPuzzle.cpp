/**
* Initial source code modified by MattJAshworth on 02/04/17.
* Final commit by MattJAshworth on 28/04/17.
* Updates at http://mattjamesashworth.com.
*/
#include "SudokuPuzzle.h"
#include <Windows.h>
#include <fstream>
#include <algorithm>

SudokuPuzzle::SudokuPuzzle()
{
}

SudokuPuzzle::~SudokuPuzzle()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			delete gridRows[i].GetCell(j);
		}
	}
}

void SudokuPuzzle::ReadToGrid(char filenameIn[])
{
	std::fstream fin(filenameIn);
	CellObj *entireGrid[9][9];

	if (fin.is_open())
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int col = 0; col < 9; ++col)
			{
				int c;
				CellObj *cell;

				fin >> c;

				if (c == 0)
				{
					cell = new CellObj();
				}
				else
				{
					cell = new CellObj(c);
				}

				entireGrid[row][col] = cell;
			}
		}
		fin.close();
	}

	int group = 0;
	int index = 0;

	for (int rows = 0; rows < 9; ++rows)
	{
		if (rows % 3 == 0 && rows != 0)
		{
			group = group + 3;
			index = 0;
		}

		for (int cols = 0; cols < 9; ++cols)
		{
			gridRows[rows].SetCell(cols, entireGrid[rows][cols]);
			gridColumns[cols].SetCell(rows, entireGrid[rows][cols]);
			gridBlocks[group].SetCell(index, entireGrid[rows][cols]);

			++index;

			if ((cols + 1) % 9 == 0)
			{
				group = group - 2;
			}
			else if ((cols + 1) % 3 == 0)
			{
				group = ++group;
				index -= 3;
			}
		}
	}
}

void SudokuPuzzle::Solve(char filenameIn[])
{
	ReadToGrid(filenameIn);

	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	bool hiddenStop;
	bool nakedStop;
	CellObj* checkCell;

	InitSolve();

	// Solve the puzzles
	do
	{
		int checkBlock = 0;
		int index = 0;
		hiddenStop = false;
		nakedStop = false;
		meta.IncrementPasses();

		//For every cell...
		for (int i = 0; i < 9; ++i)
		{
			if (i % 3 == 0 && i != 0)
			{
				checkBlock = checkBlock + 3;
				index = 0;
			}

			for (int j = 0; j < 9; ++j)
			{
				checkCell = gridRows[i].GetCell(j);

				if (CheckNakedSingle(checkCell, checkBlock, i, j))
				{
					nakedStop = true;
				}
				if (CheckHiddenSingle(checkCell, i, j, checkBlock, index))
				{
					hiddenStop = true;
				}

				++index;

				if ((j + 1) % 9 == 0)
				{
					checkBlock = checkBlock - 2;
				}
				else if ((j + 1) % 3 == 0)
				{
					checkBlock = ++checkBlock;
					index -= 3;
				}
			}
		}
	} while (nakedStop || hiddenStop);

	QueryPerformanceCounter(&end);

	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
	int solved = meta.GetNumberSolved();
	int passes = meta.GetNumberOfPasses();
	int possibleOut = meta.GetPossibleCandids();
	int hiddenSolved = meta.GetNumberHidden();
	int nakedSolved = meta.GetNumberNaked();

	std::cout << "TIME ELAPSED: " << time << std::endl;
	std::cout << "TOTAL SOLVED: " << solved << std::endl;
	std::cout << "NAKED SOLVED: " << nakedSolved << std::endl;
	std::cout << "HIDDEN SOLVED: " << hiddenSolved << std::endl;
	std::cout << "PASSES: " << passes << std::endl;
	std::cout << "POSSIBLE CANDIDATES: " << possibleOut << std::endl;

	Output();
}

bool SudokuPuzzle::CheckNakedSingle(CellObj* checkCell, int block, int row, int col)
{
	if (checkCell->GetCandidsLength() == 1)
	{
		int c = checkCell->GetCandidValue(0);
		checkCell->SetValue(c);
		checkCell->RemoveCandid(c, &meta);

		for (int i = 0; i < 9; ++i)
		{
			gridBlocks[block].GetCell(i)->RemoveCandid(c, &meta);
			gridRows[row].GetCell(i)->RemoveCandid(c, &meta);
			gridColumns[col].GetCell(i)->RemoveCandid(c, &meta);
		}

		meta.IncrementNaked();
		meta.IncrementSolved();

		return true;
	}
	return false;
}

bool SudokuPuzzle::CheckHiddenSingle(CellObj* checkCell, int row, int col, int block, int index)
{
	if (checkCell->GetValue() == 0)
	{
		int candSize = checkCell->GetCandidsLength();

		//for every candidate in the candidate list...
		for (int x = 0; x < candSize; ++x)
		{
			//Get the candidate...
			int c = checkCell->GetCandidValue(x);

			//Check if it is in the row, column and block...
			if (!IsIn(gridRows[row], col, c) &&
				!IsIn(gridColumns[col], row, c) &&
				!IsIn(gridBlocks[block], index, c))
			{
				//If not then it is unique to that cell so solve it...
				checkCell->SetValue(c);
				checkCell->EmptyCandids();

				meta.IncrementHidden();
				meta.IncrementSolved();
				return true;
			}
		}
	}
	return false;
}

bool SudokuPuzzle::NarrowCandidates(CellObj* checkCell, int checkCellRow, int checkCellColumn, int checkBlock)
{
	CellObj* comparisonCell;

	for (int j = 0; j < 9; ++j)
	{
		if (checkCell->GetCandidsLength() == 0)
		{
			return false;
		}

		//Checks the row...
		if (j != checkCellColumn)
		{
			comparisonCell = gridRows[checkCellRow].GetCell(j);

			if (comparisonCell->GetValue() != 0)
			{
				checkCell->RemoveCandid(comparisonCell->GetValue(), &meta);
			}

			//Check block...
			comparisonCell = gridBlocks[checkBlock].GetCell(j);

			if (comparisonCell->GetValue() != 0)
			{
				checkCell->RemoveCandid(comparisonCell->GetValue(), &meta);
			}
		}

		//Check the column...
		if (j != checkCellRow)
		{
			comparisonCell = gridColumns[checkCellColumn].GetCell(j);

			if (comparisonCell->GetValue() != 0)
			{
				checkCell->RemoveCandid(comparisonCell->GetValue(), &meta);
			}
		}
	}
	return true;
}

void SudokuPuzzle::InitSolve()
{
	int checkBlock = 0;
	int index = 0;
	CellObj* checkCell;

	meta.IncrementPasses();

	//For every cell...
	for (int i = 0; i < 9; ++i)
	{
		if (i % 3 == 0 && i != 0)
		{
			checkBlock = checkBlock + 3;
			index = 0;
		}

		for (int j = 0; j < 9; ++j)
		{
			checkCell = gridRows[i].GetCell(j);

			NarrowCandidates(checkCell, i, j, checkBlock);
			++index;

			if ((j + 1) % 9 == 0)
			{
				checkBlock = checkBlock - 2;
			}
			else if ((j + 1) % 3 == 0)
			{
				checkBlock = ++checkBlock;
				index -= 3;
			}
		}
	}
}

bool SudokuPuzzle::IsIn(const Blocks &cellGroup, int currentCell, int value)
{
	//For each cell in the cellgroup...
	for (int cell = 0; cell < 9; ++cell)
	{
		//If not the cell we are inspecting...
		if (currentCell != cell)
		{
			//...then check if the cell contains the candidate we are looking for.
			if (cellGroup.GetCell(cell)->Contains(value, &meta))
			{
				//If it does then return true which means the candidate is not unique.
				return true;
			}
		}
		else
		{
			//Go around the loop again.
			continue;
		}
	}
	return false;
}

void SudokuPuzzle::Output() const
{
	ofstream fout("sudoku_solution.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				fout << gridRows[i].GetValue(j) << " ";
			}

			fout << endl;
		}
		fout.close();
	}
}
