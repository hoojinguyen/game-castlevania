#include "Wall.h"
#include "Camera.h"

Wall::Wall()
{
}

Wall::Wall(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Wall::Render()
{
	RenderBoundingBox();
}


void Wall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}


Wall::~Wall()
{
}
