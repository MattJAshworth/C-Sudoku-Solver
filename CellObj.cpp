/**
* Created by MattJAshworth on 05/04/17.
* Final commit by MattJAshworth on 28/04/17.
* Updates at http://mattjamesashworth.com.
*/
#include "CellObj.h"
#include "vector"

CellObj::CellObj() : value(0), hardcode(false)
{
	InitCandids();  //Candids for CellObject(s) (CellObj)
}

CellObj::CellObj(int num) : value(num), hardcode(true)
{
}

CellObj::~CellObj()
{
}

int CellObj::GetValue() const
{
	return value; //Return value of Cell
}

void CellObj::SetValue(int num)
{
	value = num;  //Set Value of Cell
}

bool CellObj::GetHardcoded() const
{
	return hardcode;  //Return whether hardcoded from file
}

void CellObj::InitCandids()
{
	for (int i = 1; i < 10; ++i)
	{
		candidList.push_back(i);
	}
}

void CellObj::RemoveCandid(const int value, MetaLog* meta)  //Method to remove candidate value from candidate list
{
	for (int i = 0; i < candidList.size(); ++i)
	{
		meta->IncrementPossibleCandids();
		if (value == candidList[i])
		{
			candidList.erase(candidList.begin() + i);
			break;
		}
	}
}

int CellObj::GetCandidValue(int index)
{
	return candidList[index];
}

int CellObj::GetCandidsLength() const
{
	return candidList.size();
}

bool CellObj::Contains(int value, MetaLog* meta)
{
	for (int i = 0; i < candidList.size(); ++i)
	{
		meta->IncrementPossibleCandids();
		if (value == candidList[i])
			return true;
	}
	return false;
}

void CellObj::EmptyCandids()
{
	candidList.clear();
}