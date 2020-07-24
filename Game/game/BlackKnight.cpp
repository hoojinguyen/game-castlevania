#include "BlackKnight.h"
#include "Define.h"

BlackKnight::BlackKnight(float startX, float startY, int hp, int damage, float distanceGoX, int point)
{
	this->startX = startX;
	this->startY = startY;
	this->xRespawn = startX;
	this->yRespawn = startY;
	this->hp = hp;
	this->hpC = hp;
	this->damage = damage;
	this->distanceGoX = distanceGoX;
	this->point = point;

	isEnable = true;

	SetState(BLACK_KNIGHT_STATE_WALKING);

	Enemy::Enemy();
}

BlackKnight::~BlackKnight()
{
}

void BlackKnight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	Enemy::Update(dt, coObject);

	if (Enemy::isStop)
	{
		return;
	}

	if (!isDeadth && isEnable) {
		x += dx;
		y += dy;

		if (vx > 0 && abs(x - startX) > distanceGoX) {
			x = startX + distanceGoX;
			vx = -vx;
			nx = -1;
		}

		if (vx < 0 && abs(startX - x) > distanceGoX) {
			x = startX - distanceGoX;
			vx = -vx;
			nx = 1;
		}
	}
}

void BlackKnight::Render()
{
	if (!isDeadth && isEnable) {
		int posX = x, posY = y;
		int ani = 0;
		switch (state)
		{
		case BLACK_KNIGHT_STATE_WALKING:
		{
			if (nx > 0) {
				ani = BLACK_KNIGHT_ANI_WALKING_RIGHT;
			}
			else {
				ani = BLACK_KNIGHT_ANI_WALKING_LEFT;
			}
			break;
		}
		case BLACK_KNIGHT_STATE_IDLE:
		{
			if (nx > 0) {
				ani = BLACK_KNIGHT_ANI_IDLE_RIGHT;
			}
			else {
				ani = BLACK_KNIGHT_ANI_IDLE_LEFT;
			}
			break;
		}
		default:
			break;
		}

		if (Enemy::isStop)
		{
			if (nx > 0) {
				ani = BLACK_KNIGHT_ANI_IDLE_RIGHT;
			}
			else {
				ani = BLACK_KNIGHT_ANI_IDLE_LEFT;
			}
		}

		animation_set->at(ani)->Render(posX, posY);

		RenderBoundingBox();
	}
	Enemy::Render();


}

void BlackKnight::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDeadth && isEnable) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		left = x;
		right = left + BLACK_KNIGHT_BBOX_WIDTH;
		top = y;
		bottom = top + BLACK_KNIGHT_BBOX_HEIGHT;
	}
}

void BlackKnight::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
	case BLACK_KNIGHT_STATE_IDLE:
		break;
	case BLACK_KNIGHT_STATE_DIE:
		isDeadth = true;
		isEnable = false;
		break;
	case BLACK_KNIGHT_STATE_WALKING:
		vx = -BLACK_KNIGHT_WALKING_SPEED;
		nx = -1;
	}
}
