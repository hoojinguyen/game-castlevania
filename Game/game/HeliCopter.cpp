#include "Helicopter.h"

Helicopter::Helicopter()
{
}

Helicopter::~Helicopter()
{
}

void Helicopter::Update(DWORD dt)
{
	CGameObject::Update(dt);
	vx = -HELICOPTER_SPEED;
	x += dx;
}

void Helicopter::Render()
{
	animation_set->at(0)->RenderWithoutCamera(x, y);
}

void Helicopter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = top = right = bottom = 0;
}
