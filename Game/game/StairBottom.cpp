#include "StairBottom.h"

StairBottom::StairBottom(int _nx)
{
	nx = _nx;
}

void StairBottom::Render()
{
	RenderBoundingBox();
}

void StairBottom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 8;
	b = y + 8;
}

StairBottom::~StairBottom()
{
}
