#include "Weapon.h"

Weapon::Weapon()
{
	isEnable = false;
}

Weapon::~Weapon()
{
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (nx > 0)
		vx = 0.2;
	else if (nx < 0)
		vx = -0.2;


	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void Weapon::ResetAnimation()
{
	ResetAni(0);
	ResetAni(1);
}

void Weapon::Render()
{
	if (nx > 0)
		animation_set->at(1)->Render(x, y);
	else if (nx < 0)
		animation_set->at(1)->Render(x, y);
}

void Weapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
