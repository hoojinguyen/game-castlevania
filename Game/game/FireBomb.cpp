#include "FireBomb.h"
#include "Ground.h"
#include "Sound.h"
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
	bool runHit = false;


	// Check AABB
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

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	// turn off collision when die 
	if (isEnable)
		CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<FireBomb*>(this)) {
				FireBomb* fireBomb = dynamic_cast<FireBomb*>(this);
				if (dynamic_cast<Ground*>(e->obj))
				{
					if (e->ny < 0) {
						fireBomb->isFiring = true;
						Sound::GetInstance()->Play(SOUND_FIREBOMB); // chạm đất thì mới playsound
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (isFiring == true)
	{
		vy = 0;
		vx = 0;
	}
	if (isEnable == true)
		vy += FIRE_BOMB_SPEED_Y * dt;


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
	if (!isEnable)
		isFiring = false;

	if (runHit) {
		Sound::GetInstance()->Play(SOUND_HIT);
	}
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

