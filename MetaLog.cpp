/**
* Created by MattJAshworth on 21/04/17.
* Final commit by MattJAshworth on 28/04/17.
* Updates at http://mattjamesashworth.com.
*/
#include "MetaLog.h"

MetaLog::MetaLog() : gridPassCounter(0), solvedCellsCounter(0), candidsPossibleCounter(0), nakedSolvedCounter(0), hiddenSolvedCounter(0)
{
}

MetaLog::~MetaLog()
{
}

int MetaLog::GetNumberOfPasses() const
{
	return gridPassCounter;
}

int MetaLog::GetNumberSolved() const
{
	return solvedCellsCounter;
}

int MetaLog::GetPossibleCandids() const
{
	return candidsPossibleCounter;
}

int MetaLog::GetNumberNaked() const
{
	return nakedSolvedCounter;
}

int MetaLog::GetNumberHidden() const
{
	return hiddenSolvedCounter;
}

void MetaLog::IncrementPasses()
{
	++gridPassCounter;
}

void MetaLog::IncrementSolved()
{
	++solvedCellsCounter;
}

void MetaLog::IncrementPossibleCandids()
{
	++candidsPossibleCounter;
}

void MetaLog::IncrementNaked()
{
	++nakedSolvedCounter;
}

void MetaLog::IncrementHidden()
{
	++hiddenSolvedCounter;
}
