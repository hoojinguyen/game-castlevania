#include "StairTop.h"

StairTop::StairTop(int _nx)
{
	nx = _nx;
}

void StairTop::Render()
{
	if (this->enableBoundingBox)
	{
		RenderBoundingBox();
	}
}

void StairTop::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 8;
	b = y + 8;
}

StairTop::~StairTop()
{
}
