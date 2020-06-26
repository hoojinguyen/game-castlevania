#include "Define.h"
#include "BrickMoving.h"

#include "Ground.h"

BrickMoving::BrickMoving()
{
	vx = -BRICK_MOVING_SPEED;
	nx = -1;
}

void BrickMoving::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 32;
	b = y + 8;
}

void BrickMoving::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		float l1, t1, r1, b1, l2, t2, r2, b2;
		GetBoundingBox(l1, t1, r1, b1);
		coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);

		if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
		{
			if (dynamic_cast<Ground*>(coObjects->at(i))) {
				x -= dx;
				vx = -vx;
				nx = -nx;
			}

		}
	}

}

void BrickMoving::Render()
{
	animation_set->at(0)->Render(x, y);
	if (this->enableBoundingBox)
	{
		RenderBoundingBox();
	}
}