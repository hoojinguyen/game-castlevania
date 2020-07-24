#include "FireBomb.h"
#include "Ground.h"
#include "BoundingMap.h"
#include "Enemy.h"
#include "Candle.h"
#include "Torch.h"
#include "Game.h"

#define FIRE_BOMB_DAMAGE 2
#define FIRE_BOMB_USE_HEART 1
#define FIRE_BOMB_SPEED_Y_DEFAULT 0.2
#define FIRE_BOMB_SPEED_Y 0.0007

FireBomb::FireBomb()
{
	useHeart = FIRE_BOMB_USE_HEART;
	damage = FIRE_BOMB_DAMAGE;
	vy = -FIRE_BOMB_SPEED_Y_DEFAULT;

	SetAnimationSet(6);
}

FireBomb::~FireBomb()
{
}


void FireBomb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 8;
	bottom = y + 8;
}


void FireBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Weapon::Update(dt, coObjects);
	if (isFiring == true)
	{
		vy = 0;
		vx = 0;
	}
	if (isEnable == true)
		vy += FIRE_BOMB_SPEED_Y * dt;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		//if (dynamic_cast<Ground*>(coObjects->at(i)))
		//{
		//	float l1, t1, r1, b1, l2, t2, r2, b2;
		//	GetBoundingBox(l1, t1, r1, b1);
		//	coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);

		//	if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)) {
		//		isFiring = true;
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
						vx = 0;
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

	if (isFiring == true)
	{
		timefiring += dt;
		if (timefiring > 1000)
		{
			isFiring = false;
			isEnable = false;
			vy = -FIRE_BOMB_SPEED_Y_DEFAULT;
			timefiring = 0;
		}
	}
	if (isEnable == false)
		isFiring = false;
}

void FireBomb::Render()
{
	if (isFiring == true) {
		animation_set->at(2)->Render(x, y - 5);
	}
	else {
		Weapon::Render();
	}

}

