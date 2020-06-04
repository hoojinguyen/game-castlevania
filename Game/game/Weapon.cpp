#include "Weapon.h"
#include "FireBomb.h"

#define SUBWEAPON_SPEED_X 0.1f

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
		vx = SUBWEAPON_SPEED_X;
	else if (nx < 0)
		vx = -SUBWEAPON_SPEED_X;

	if (dynamic_cast<FireBomb*>(this))
	{
		FireBomb* fireBomb = dynamic_cast<FireBomb*>(this);
		if (fireBomb->GetFiring() == true)
		{
			vx = 0;
			vy = 0;
		}
	}

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
		animation_set->at(0)->Render(x, y);
}

void Weapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
