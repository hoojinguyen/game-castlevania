#include "Define.h"
#include "Sound.h"
#include "Boomerang.h"
#include "Enemy.h"
#include "Torch.h"
#include "Candle.h"

#define DELTA_X 10
#define BOOMERANG_DAMAGE 2
#define BOOMERANG_USE_HEART 1
#define BOOMERANG_ATTACK_SPEED 0.15f

Boomerang::Boomerang(float _startX)
{
	useHeart = BOOMERANG_USE_HEART;
	damage = BOOMERANG_DAMAGE;
	speed = BOOMERANG_ATTACK_SPEED;
	countReturn = 0;
	startX = _startX;

	SetAnimationSet(4);
}

Boomerang::~Boomerang()
{
}

void Boomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 14;
}


void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Weapon::Update(dt, coObjects);
	bool runHit = false;

	Sound::GetInstance()->Play(SOUND_BOOMERANG);

	//if (!CCamera::GetInstance()->CheckPositionInboundCamera(x, y))
	//{
	//	isEnable = false;
	//	Sound::GetInstance()->Stop(SOUND_BOOMERANG);
	//}

	if (vx > 0 && abs(x - startX) >= SCREEN_WIDTH / 2 - DELTA_X) {
		x = startX + SCREEN_WIDTH / 2 - DELTA_X;
		vx = -vx;
		nx = -1;
		countReturn++;
	}

	if (vx < 0 && x <= startX - SCREEN_WIDTH / 2 + DELTA_X) {
		x = startX - SCREEN_WIDTH / 2 + DELTA_X;
		vx = -vx;
		nx = 1;
		countReturn++;
	}

	if (countReturn > 1) {
		isEnable = false;
		return;
	}

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

void Boomerang::Render()
{
	Weapon::Render();
	if (this->isEnable == false)
		count = 0;
}