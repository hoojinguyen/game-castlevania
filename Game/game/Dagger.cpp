#include "Dagger.h"
#include "Ground.h"
#include "BoundingMap.h"
#include "Enemy.h"

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Weapon::Update(dt, coObjects);
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Ground*>(coObjects->at(i)) || dynamic_cast<BoundingMap*>(coObjects->at(i)))
		{
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);
			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)) {
				isEnable = false;
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
					if (enemy->isEnable != false) {
						enemy->SetHP(enemy->GetHP() - this->damage);
						enemy->GetCollisionEffect()->SetEnable(true);
						isEnable = false;
					}
				}
			}

		}
	}
}

void Dagger::Render()
{
	Weapon::Render();
}

void Dagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (nx > 0)
	{
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 9;
	}
	else
	{
		left = x - 16;
		top = y;
		right = left + 16;
		bottom = y + 9;
	}
}

Dagger::Dagger()
{
	SetAnimationSet(3);
	useHeart = 1;
	damage = 1;
}

Dagger::~Dagger()
{
}
