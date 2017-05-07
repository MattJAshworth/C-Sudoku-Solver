#pragma once
class MetaLog
{
public:
	MetaLog();
	~MetaLog();

	int GetNumberSolved() const;
	int GetNumberHidden() const;
	int GetNumberNaked() const;			//Metadata variables holding data about number of passes, Solved Cells, etc...
	int GetNumberOfPasses() const;
	int GetPossibleCandids() const; 

	//Methods
	void IncrementPasses();
	void IncrementSolved();
	void IncrementPossibleCandids();	//Update methods for metadata
	void IncrementNaked();	
	void IncrementHidden();

private:
	int gridPassCounter;
	int solvedCellsCounter;
	int candidsPossibleCounter;
	int nakedSolvedCounter;
	int hiddenSolvedCounter;
};

