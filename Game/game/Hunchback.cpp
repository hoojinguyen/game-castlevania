#include "Hunchback.h"
#include "Define.h"
#include "Simon.h"
#include "Ground.h"

Hunchback::Hunchback(float startX, float startY, int hp, int damage, float distanceAttack, int point)
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
	timeJump = 0;

	SetState(HUNCHBACK_STATE_IDLE);

	Enemy::Enemy();
}

Hunchback::~Hunchback()
{
}

void Hunchback::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	Enemy::Update(dt, coObjects);

	if (Enemy::isStop)
	{
		return;
	}

	if (!isDeadth && isEnable)
	{

		float simonX, simonY;

		Simon::GetInstance()->GetPosition(simonX, simonY);

		nx = this->x >= simonX ? -1 : 1;

		if (state != HUNCHBACK_STATE_IDLE)
		{
			vy += HUNCHBACK_GRAVITY * dt;
		}
		else if (state == HUNCHBACK_STATE_IDLE)
		{
			if (abs(this->x - simonX) <= this->distanceAttack)
			{
				SetState(HUNCHBACK_STATE_JUMP);
			}
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			bool isCollision = false;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
			//if (rdx != 0 && rdx!=dx)
			//	x += nx*abs(rdx);

			// block every object first!

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<Ground *>(e->obj)) // if e->obj is Goomba
				{
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;

					if (nx != 0)
						vx = 0;
					if (ny != 0)
						vy = 0;

					if (state != HUNCHBACK_STATE_IDLE)
					{
						SetState(HUNCHBACK_STATE_ATTACK);
					}

				/*	if (state == HUNCHBACK_STATE_ATTACK && GetTickCount() > timeJump + 200)
					{
						SetState(HUNCHBACK_STATE_IDLE);
					}*/

					isCollision = true;
				}
			}

			if (!isCollision)
			{
				x += dx;
				y += dy;
			}
		}
	}
}

void Hunchback::Render()
{
	if (!isDeadth && isEnable)
	{
		int posX = x, posY = y;
		int ani = 0;
		switch (state)
		{
		case HUNCHBACK_STATE_IDLE:
		{
			if (nx > 0)
			{
				ani = HUNCHBACK_ANI_IDLE_RIGHT;
			}
			else
			{
				ani = HUNCHBACK_ANI_IDLE_LEFT;
			}
		}
		break;
		case HUNCHBACK_STATE_JUMP:
		case HUNCHBACK_STATE_ATTACK:
		{
			if (nx > 0)
			{
				ani = HUNCHBACK_ANI_ATTACK_RIGHT;
			}
			else
			{
				ani = HUNCHBACK_ANI_ATTACK_LEFT;
			}
		}
		break;
		default:
			break;
		}

		animation_set->at(ani)->Render(posX, posY);
		if (this->enableBoundingBox)
		{
			RenderBoundingBox();
		}
	}

	Enemy::Render();
}

void Hunchback::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isDeadth)
	{
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else
	{
		left = x;
		right = left + HUNCHBACK_BBOX_WIDTH;
		top = y;
		bottom = top + HUNCHBACK_BBOX_HEIGHT;
	}
}

void Hunchback::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
	case HUNCHBACK_STATE_IDLE:
		break;
	case HUNCHBACK_STATE_JUMP:
		if (nx > 0)
		{
			vx = HUNCHBACK_JUMP_SPEED_X;
		}
		else
		{
			vx = -HUNCHBACK_JUMP_SPEED_X;
		}

		vy = -HUNCHBACK_JUMP_SPEED_Y;
		break;
	case HUNCHBACK_STATE_ATTACK:
	{
		if (nx > 0)
		{
			vx = HUNCHBACK_SPEED_X;
		}
		else
		{
			vx = -HUNCHBACK_SPEED_X;
		}

		DWORD now = GetTickCount();

		if (timeJump == 0)
		{
			timeJump = now;
			vy = -HUNCHBACK_SPEED_Y;
		}
		else if (now - timeJump >= 2000)
		{
			timeJump = now;
			vy = -HUNCHBACK_SPEED_Y * 2;
		}
		else
		{
			vy = -HUNCHBACK_SPEED_Y;
		}
	}
	break;
	}
}
