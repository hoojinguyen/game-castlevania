#include "Brick.h"
#include "Define.h"

Brick::Brick()
{
}

void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 32;
	b = y + 32;
}

void Brick::Render()
{
	switch (type)
	{
	default:
		break;
	}

	RenderBoundingBox();
}

