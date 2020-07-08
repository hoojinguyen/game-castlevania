#include "Zombie.h"
#include "Define.h"
#include "Ground.h"
#include "BoundingMap.h"
#include "Simon.h"

Zombie::Zombie(float startX, float startY)
{
	this->startX = startX;
	this->startY = startY;

	hp = 1;

	damage = 2;
	point = 100;

	Enemy::Enemy();

	SetState(ZOOMBIE_STATE_IDLE);
}

Zombie::~Zombie()
{
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	if (!isDeadth && isEnable) {

		float simonX, simonY;

		Simon::GetInstance()->GetPosition(simonX, simonY);

		nx = this->x >= simonX ? -1 : 1;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (!(dynamic_cast<Ground*>(e->obj) || dynamic_cast<BoundingMap*>(e->obj)))
				coEvents.erase(coEvents.begin() + i);
		}

		if (coEvents.size() == 0) {

			x += dx;
			y += dy;

			isGrounded = false;
		}
		else {
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
			//if (rdx != 0 && rdx!=dx)
			//	x += nx*abs(rdx); 

			// block every object first!

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<Ground*>(e->obj))
				{
					isGrounded = true;
					if (e->ny < 0)
					{
						x +=  dx;
						y += min_ty * dy + ny * 0.1f;
						if (ny != 0) vy = 0;
					}
					if (e->nx != 0)
					{
						x +=  dx;
						y += 1;
						if (ny != 0) vy = 0;
					}
				}

				if (dynamic_cast<BoundingMap*>(e->obj))
				{
					SetState(ZOOMBIE_STATE_WALKING);
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++)
		{
			delete coEvents[i];
		}
		/*if (!isGrounded)
			vy += 0.001 * dt;*/
	}
}

void Zombie::Render()
{
	if (!isDeadth && isEnable) {
		int posX = x, posY = y;
		int ani = 0;
		switch (state)
		{
		case ZOOMBIE_STATE_WALKING:
		{
			if (nx > 0) {
				ani = ZOOMBIE_ANI_WALKING_RIGHT;
			}
			else {
				ani = ZOOMBIE_ANI_WALKING_LEFT;
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

void Zombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDeadth) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		left = x;
		right = left + ZOOMBIE_BBOX_WIDTH;
		top = y;
		bottom = top + ZOOMBIE_BBOX_HEIGHT;
	}
}

void Zombie::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
	case ZOOMBIE_STATE_WALKING:
		vx = nx * ZOOMBIE_WALKING_SPEED;
	case ZOOMBIE_STATE_IDLE:
		vx = 0;
		break;
	}
}
