#include "Ghost.h"
#include "Define.h"
#include "Simon.h"

Ghost::Ghost(float startX, float startY)
{
	this->startX = startX;
	this->startY = startY;

	this->hp = GHOST_HP;
	isEnable = true;
	damage = GHOST_DAMAGE;

	Enemy::Enemy();

	SetState(GHOST_STATE_HIDE);

	point = 300;
}

Ghost::~Ghost()
{
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT> *coObject)
{
	Enemy::Update(dt, coObject);
	if (!isDeadth && isEnable)
	{

		float simonX, simonY;

		Simon::GetInstance()->GetPosition(simonX, simonY);

		nx = this->x >= simonX ? -1 : 1;

		if (state == GHOST_STATE_FLYING)
		{
			x += dx;
			y += dy;

			if (nx > 0)
			{
				if (abs(this->x - simonX) <= GHOST_DISTANCE_WAITING_X + SIMON_BBOX_WIDTH && abs(this->y - simonY) < SIMON_BBOX_HEIGHT)
				{
					SetState(GHOST_STATE_WAITTING);
				}
			}
			else
			{
				if (abs(this->x - simonX) <= GHOST_DISTANCE_WAITING_X && abs(this->y - simonY) < SIMON_BBOX_HEIGHT)
				{
					SetState(GHOST_STATE_WAITTING);
				}
			}
		}
		else if (state == GHOST_STATE_HIDE)
		{
			if (abs(this->x - simonX) >= GHOST_DISTANCE_ATTACK_X && abs(this->y - simonY) < SIMON_BBOX_HEIGHT)
			{
				SetState(GHOST_STATE_FLYING);
			}
		}
	}
}

void Ghost::Render()
{
	if (!isDeadth && isEnable && state != GHOST_STATE_HIDE)
	{
		int ani = 0;
		switch (state)
		{
		case GHOST_STATE_WAITTING:
		case GHOST_STATE_FLYING:
		{
			if (nx > 0)
			{
				ani = GHOST_ANI_FLYING_RIGHT;
			}
			else
			{
				ani = GHOST_ANI_FLYING_LEFT;
			}
		}
		break;
		default:
			break;
		}

		animation_set->at(ani)->Render(x, y);
		RenderBoundingBox();
	}

	Enemy::Render();
}

void Ghost::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isDeadth || state == GHOST_STATE_HIDE)
	{
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else
	{
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
		if (nx > 0)
		{
			vx = GHOST_FLYING_SPEED_X;
		}
		else
		{
			vx = -GHOST_FLYING_SPEED_X;
		}
		break;
	case GHOST_STATE_WAITTING:
		vx = 0;
		break;
	}
}
