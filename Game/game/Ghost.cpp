#include "Ghost.h"
#include "Define.h"
#include "Simon.h"

Ghost::Ghost(float startX, float startY, int hp, int damage, float distanceAttack, int point)
{
	this->startX = startX;
	this->startY = startY;
	this->xRespawn = startX;
	this->yRespawn = startY;
	this->hp = hp;
	this->hpC = hp;
	this->damage = damage;
	this->distanceAttack = distanceAttack;
	this->point = point;
	isEnable = true;

	SetState(GHOST_STATE_HIDE);

	Enemy::Enemy();
}

Ghost::~Ghost()
{
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	Enemy::Update(dt, coObject);

	if (Enemy::isStop)
	{
		return;
	}

	if (!isDeadth && isEnable)
	{
		float simonX, simonY;

		Simon::GetInstance()->GetPosition(simonX, simonY);

		nx = this->x >= simonX ? -1 : 1;
		ny = this->y >= simonY ? -1 : 1;
		if (state == GHOST_STATE_FLYING)
		{
			if (nx > 0) {
				vx = GHOST_FLYING_SPEED_X;
			}
			else {
				vx = -GHOST_FLYING_SPEED_X;
			}

			if (ny > 0) {
				vy = GHOST_FLYING_SPEED_X;
			}
			else {
				vy = -GHOST_FLYING_SPEED_X;
			}

			if (abs(this->x - simonX) >= SIMON_BBOX_WIDTH / 2)
			{
				x += dx;
			}

			if (!(simonY <= this->y && this->y - simonY <= GHOST_BBOX_HEIGHT / 2)) {
				y += dy;
			}
		}
		else if (state == GHOST_STATE_HIDE) {
			if (nx < 0) {
				if (this->x - (simonX + SIMON_BBOX_WIDTH) >= this->distanceAttack) {
					SetState(GHOST_STATE_FLYING);
				}
			}
			else {
				if (simonX - (this->x + GHOST_BBOX_WIDTH) >= this->distanceAttack) {
					SetState(GHOST_STATE_FLYING);
				}
			}
		}
	}
}

void Ghost::Render()
{
	if (!isDeadth && isEnable && state != GHOST_STATE_HIDE) {
		int ani = 0;
		switch (state)
		{
		case GHOST_STATE_WAITTING:
		case GHOST_STATE_FLYING:
		{
			if (nx > 0) {
				ani = GHOST_ANI_FLYING_RIGHT;
			}
			else {
				ani = GHOST_ANI_FLYING_LEFT;
			}
		}
		break;
		default:
			break;
		}

		if (Enemy::isStop)
		{
			if (nx > 0) {
				ani = GHOST_ANI_IDLE_RIGHT;
			}
			else {
				ani = GHOST_ANI_IDLE_LEFT;
			}
		}

		animation_set->at(ani)->Render(x, y);

		RenderBoundingBox();
	}

	Enemy::Render();
}

void Ghost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDeadth || state == GHOST_STATE_HIDE) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		left = x;
		right = left + GHOST_BBOX_WIDTH;
		top = y;
		bottom = top + GHOST_BBOX_HEIGHT;
	}
}

void Ghost::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
	case GHOST_STATE_DIE:
		isDeadth = true;
		isEnable = false;
		break;
	case GHOST_STATE_HIDE:
		break;
	case GHOST_STATE_FLYING:
		if (nx > 0) {
			vx = GHOST_FLYING_SPEED_X;
		}
		else {
			vx = -GHOST_FLYING_SPEED_X;
		}

		if (ny > 0) {
			vy = GHOST_FLYING_SPEED_X;
		}
		else {
			vy = -GHOST_FLYING_SPEED_X;
		}
		break;
	case GHOST_STATE_WAITTING:
		vx = 0;
		break;
	}
}
