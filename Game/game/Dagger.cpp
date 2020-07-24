#include "Dagger.h"
#include "Ground.h"
#include "BoundingMap.h"
#include "Enemy.h"
#include "Torch.h"
#include "Candle.h"

#define DAGGER_DAMAGE 1
#define DAGGER_USE_HEART 1

Dagger::Dagger()
{
	damage = DAGGER_DAMAGE;
	useHeart = DAGGER_USE_HEART;
	SetAnimationSet(3);
}

Dagger::~Dagger()
{
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


void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Weapon::Update(dt, coObjects);

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		//if (dynamic_cast<Ground*>(coObjects->at(i)) || dynamic_cast<BoundingMap*>(coObjects->at(i)))
		//{
		//	float l1, t1, r1, b1, l2, t2, r2, b2;
		//	GetBoundingBox(l1, t1, r1, b1);
		//	coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);
		//	if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)) {
		//		isEnable = false;
		//	}
		//}
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
		if (dynamic_cast<Candle*>(coObjects->at(i))) {
			Candle* candle = dynamic_cast<Candle*>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			candle->GetBoundingBox(l2, t2, r2, b2);
			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)) {
				if (candle->isEnable) {
					candle->GetCollisionEffect()->SetEnable(true);
					candle->GetDeadEffect()->SetEnable(true);
					candle->isEnable = false;
					candle->isDeadth = true;
					isEnable = false;
				}
			}
		}
		if (dynamic_cast<Torch*>(coObjects->at(i))) {
			Torch* torch = dynamic_cast<Torch*>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			torch->GetBoundingBox(l2, t2, r2, b2);
			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)) {
				if (torch->isEnable) {
					torch->GetCollisionEffect()->SetEnable(true);
					torch->GetDeadEffect()->SetEnable(true);
					torch->isEnable = false;
					torch->isDeadth = true;
					isEnable = false;
				}
			}
		}
	}
}

void Dagger::Render()
{
	Weapon::Render();
}