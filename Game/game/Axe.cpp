#include "Axe.h"
#include "Ground.h"
#include "Sound.h"
#include "BoundingMap.h"
#include "Enemy.h"
#include "Torch.h"
#include "Candle.h"

#define AXE_SPEED_Y_DEFAULT 0.25
#define AXE_SPEED_Y 0.0007
#define AXE_DAMAGE 3
#define AXE_USE_HEART 1

Axe::Axe()
{
	useHeart = AXE_USE_HEART;
	damage = AXE_DAMAGE;
	vy = -AXE_SPEED_Y_DEFAULT;

	SetAnimationSet(5);
}

Axe::~Axe()
{
}

void Axe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 14;
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Weapon::Update(dt, coObjects);
	bool runHit = false;

	Sound::GetInstance()->Play(SOUND_AXE);

	if (!CCamera::GetInstance()->CheckPositionInboundCamera(x, y))
	{
		isEnable = false;
		Sound::GetInstance()->Stop(SOUND_AXE);
	}

	if (isEnable) {
		vy += AXE_SPEED_Y * dt;
	}


	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy*>(coObjects->at(i))) {
			Enemy* enemy = dynamic_cast<Enemy*>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);
			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)) {
				if ((coObjects->at(i))->nx != 0)
				{
					if (enemy->isEnable != false) {
						runHit = true;
						enemy->SetHP(enemy->GetHP() - damage);
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
					runHit = true;
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
					runHit = true;
					torch->GetCollisionEffect()->SetEnable(true);
					torch->GetDeadEffect()->SetEnable(true);
					torch->isEnable = false;
					torch->isDeadth = true;
					isEnable = false;
				}
			}
		}
	}
	if (runHit) {
		Sound::GetInstance()->Play(SOUND_HIT);
	}
}

void Axe::Render()
{
	Weapon::Render();
}



