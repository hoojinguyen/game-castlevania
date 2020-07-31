#include "BrokenBrickEffect.h"
#include "Define.h"

BrokenBrickEffect::BrokenBrickEffect()
{
}

BrokenBrickEffect::BrokenBrickEffect(int type) : CGameObject()
{
	this->type = type;
	SetAnimationSet(341);
	timeStart = 0;
}

void BrokenBrickEffect::Render()
{
	if (isEnable)
		animation_set->at(0)->Render(x, y);
}

void BrokenBrickEffect::Update(DWORD dt)
{
	if (!isEnable) return;
	CGameObject::Update(dt);
	vy += BONE_GRAVITY * dt;

	x += dx;
	y += dy;

	if (GetTickCount() - timeStart >= 1500 && timeStart > 0) {
		isEnable = false;
	}
}

void BrokenBrickEffect::Enable(float x, float y)
{
	this->x = x;
	this->y = y;
	SetEnable(true);
	timeStart = GetTickCount();
	switch (type)
	{
	case 0:
		nx = -1;
		vx = nx * 0.06;
		vy = -0.02;
		break;
	case 1:
		nx = -1;
		vx = nx * 0.001;
		vy = -0.02;
		break;
	case 2:
		nx = 1;
		vx = nx * 0.06;
		vy = -0.03;
		break;
	case 3:
		nx = 1;
		vx = nx * 0.06;
		vy = -0.2;
		break;
	default:
		break;
	}
}

void BrokenBrickEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}
