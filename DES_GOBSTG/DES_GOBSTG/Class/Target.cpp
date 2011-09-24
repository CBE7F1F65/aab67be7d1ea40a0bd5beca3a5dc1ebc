#include "../header/Target.h"

Target Target::tar[TARGETMAX];

void Target::ClearAll()
{
	for (int i=0; i<TARGETMAX; i++)
	{
		SetValue(i, 0, 0);
	}
}

void Target::SetValue(int index, float x, float y)
{
	tar[index].x = x;
	tar[index].y = y;
}