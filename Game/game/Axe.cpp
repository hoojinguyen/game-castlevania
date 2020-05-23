#include "Axe.h"
#include "Ground.h"
#include "BoundingMap.h"
#include "Enemy.h"

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isEnable)
		vy += 0.000900 * dt;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if ((dynamic_cast<Ground*>(coObjects->at(i)) || dynamic_cast<BoundingMap*>(coObjects->at(i))))
		{
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);
			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)) {
				vy = -0.4;
				isEnable = false;
			}
		}
		if (dynamic_cast<Enemy*>(coObjects->at(i))) {
			Enemy* enemy = dynamic_cast<Enemy*>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);
			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)) {
				if ((coObjects->at(i))->nx != 0)
				{
					if (enemy->isEnable != false) {
						enemy->SetHP(enemy->GetHP() - damage);
						enemy->GetCollisionEffect()->SetEnable(true);
					}
					isEnable = false;
				}
			}
		}
	}
}

void Axe::Render()
{
	Weapon::Render();
}

void Axe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 14;
}

Axe::Axe()
{
	SetAnimationSet(5);
	useHeart = 1;
	damage = 2;
	vy = -0.4;
}

Axe::~Axe()
{
}
