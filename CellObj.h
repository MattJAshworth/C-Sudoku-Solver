#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "MetaLog.h"

class CellObj
{
public:
	explicit CellObj();
	explicit CellObj(int num);
	~CellObj();

	//Methods
	void SetValue(int num);
	int GetValue() const;

	bool GetHardcoded() const; // Get result of hardcode

	void InitCandids();
	void EmptyCandids();
	bool Contains(const int value, MetaLog* meta);
	int GetCandidsLength() const;
	void RemoveCandid(const int value, MetaLog* meta);
	int GetCandidValue(const int index);

private:
	std::vector<int> candidList;
	bool hardcode; //Bool to determine whether cell value was determined by the input file or program
	int value;
};

