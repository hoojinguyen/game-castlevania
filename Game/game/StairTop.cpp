#include "StairTop.h"

StairTop::StairTop(int _nx)
{
	nx = _nx;
}

void StairTop::Render()
{
	RenderBoundingBox();
}

void StairTop::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 8;
}

StairTop::~StairTop()
{
}
