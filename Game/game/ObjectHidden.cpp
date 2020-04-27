#include "ObjectHidden.h"

CObjectHidden::CObjectHidden(float _x, float _y, int _with, int _height, int scene_id)
{
	this->scene_id = scene_id;
	x = _x;
	y = _y;
	width = _with;
	height = _height;
}

void CObjectHidden::Render()
{
	RenderBoundingBox();
}

void CObjectHidden::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}