#include "FireBomb.h"
#include "Ground.h"
#include "BoundingMap.h"
#include "Enemy.h"

void FireBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (IsFiring == true)
	{
		vy = 0;
		vx = 0;
	}
	if (isEnable == true)
		vy += 0.000900 * dt;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Ground*>(coObjects->at(i)))
		{
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);

			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)) {
				IsFiring = true;
			}
		}
		if (dynamic_cast<Enemy*>(coObjects->at(i))) {

			Enemy* enemy = dynamic_cast<Enemy*>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);

			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if ((coObjects->at(i))->nx != 0)
				{
					if (!enemy->isEnable) {
						vx = 0;
						enemy->SetHP(enemy->GetHP() - this->damage);
						enemy->GetCollisionEffect()->SetEnable(true);
					}
				}
			}

		}
	}

	if (IsFiring == true)
	{
		timefiring += dt;
		if (timefiring > 1000)
		{
			IsFiring = false;
			isEnable = false;
			vy = -0.4;
			timefiring = 0;
		}
	}
	if (isEnable == false)
		IsFiring = false;
}

void FireBomb::Render()
{
	Weapon::Render();
	if (IsFiring == true)
		animation_set->at(2)->Render(x, y);
}

void FireBomb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 8;
	bottom = y + 8;
}

FireBomb::FireBomb()
{
	useHeart = 1;
	damage = 2;
	vy = -0.4;
	SetAnimationSet(6);
}

FireBomb::~FireBomb()
{
}
