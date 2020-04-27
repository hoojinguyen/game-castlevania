#include "BoundingMap.h"
#include "Camera.h"

BoundingMap::BoundingMap()
{
}

void BoundingMap::Render()
{
	RenderBoundingBox();
}


void BoundingMap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

BoundingMap::BoundingMap(int width, int height)
{
	this->width = width;
	this->height = height;
}


BoundingMap::~BoundingMap()
{
}
