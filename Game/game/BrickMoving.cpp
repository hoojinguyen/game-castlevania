#include "Define.h"
#include "BrickMoving.h"

#include "Ground.h"

#define DISTANCE_START 32

BrickMoving::BrickMoving()
{
	vx = -BRICK_MOVING_SPEED;
	nx = 1;
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
	CGameObject::Update(dt);
	x += dx;
	if (vx > 0 && abs(x - DISTANCE_START) > 32) {
		x = DISTANCE_START + 32;
		vx = -vx;
		nx = -1;
	}

	if (vx < 0 && x <= DISTANCE_START) {
		x = DISTANCE_START;
		vx = -vx;
		nx = 1;
	}

}

void BrickMoving::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}