#pragma once

#include "CellObj.h"

class Blocks
{
public:
	Blocks(void);
	~Blocks(void);

	void SetCell(int index, CellObj *cellobj);
	CellObj* GetCell(const int index) const;
	int GetValue(const int index) const;
	void Init();

private:
	CellObj* cells[9];
};

