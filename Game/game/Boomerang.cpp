#include "Boomerang.h"
#include "Enemy.h"

void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy*>(coObjects->at(i))) {
			Enemy* enemy = dynamic_cast<Enemy*>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);
			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if ((coObjects->at(i))->nx != 0)
				{
					if (enemy->isEnable != false) {
						enemy->SetHP(enemy->GetHP() - damage);
						enemy->GetCollisionEffect()->SetEnable(true);
					}
				}
			}
		}
	}
}

void Boomerang::Render()
{
	Weapon::Render();
	if (this->isEnable == false)
		count = 0;
}

void Boomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 14;
}

Boomerang::Boomerang()
{
	SetAnimationSet(4);
	useHeart = 1;
	damage = 2;
}

Boomerang::~Boomerang()
{
}
