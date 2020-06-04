#include "Boomerang.h"
#include "Enemy.h"
#include "Define.h"

#define DELTA_X 10
#define BOOMERANG_DAMAGE 2
#define BOOMERANG_USE_HEART 1

Boomerang::Boomerang(float _startX)
{
	useHeart = BOOMERANG_USE_HEART;
	damage = BOOMERANG_DAMAGE;

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