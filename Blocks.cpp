/**
* Created by MattJAshworth on 05/04/17.
* Final commit by MattJAshworth on 28/04/17.
* Updates at http://mattjamesashworth.com.
*/
#include "Blocks.h"
#include <iostream>

Blocks::Blocks()
{
	Init();
}

Blocks::~Blocks()
{

}

void Blocks::Init()
{
	for (int i = 0; i < 9; ++i)
	{
		cells[i] = NULL;
	}
}

int Blocks::GetValue(int index) const
{
	return cells[index]->GetValue();
}

void Blocks::SetCell(int index, CellObj *cellobj)
{
	cells[index] = cellobj;
}

CellObj* Blocks::GetCell(int index) const
{
	return cells[index];
}
