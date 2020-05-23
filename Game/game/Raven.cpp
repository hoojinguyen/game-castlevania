#include "Raven.h"
#include "Ground.h"
#include "Simon.h"
#include "Define.h"

Raven::Raven(float startX, float startY)
{
	this->x = startX;
	this->y = startY;

	this->hp = RAVEN_HP;
	isEnable = true;

	damage = RAVEN_DAMAGE;

	Enemy::Enemy();

	SetState(RAVEN_STATE_IDLE);
	
}

Raven::~Raven()
{
}

void Raven::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		// Simon se khong va cham voi nhung vat sau:
		if (dynamic_cast<Ground*>(coObjects->at(i)))
		{
			Ground* ground = dynamic_cast<Ground*>(coObjects->at(i));
			float gl, gr, gt, gb;
			ground->GetBoundingBox(gl, gt, gr, gb);

			if (x < gr && x + RAVEN_BBOX_WIDTH > gl&&
				y < gb && y + RAVEN_BBOX_HEIGHT > gt&&
				vy > 0)
			{
				// Xét va chạm cứng
				SetState(RAVEN_STATE_IDLE);
				isStickToGround = true;
				idleCast = GetTickCount();
			}

			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

			if (e->t > 0 && e->t <= 1.0f && vy > 0)
				coEvents.push_back(e);
			else
				delete e;
		}
	}
}


void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
		Enemy::Update(dt, coObjects);

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		CalcPotentialCollisions(coObjects, coEvents);


		if (isIdle)
		{
			float simonX, simonY;

			Simon::GetInstance()->GetPosition(simonX, simonY);

			if (simonX < x + 100.0f) {
				SetState(RAVEN_STATE_JUMP);
			}

			/*
			if (GetTickCount() - idleCast > RAVEN_IDLE_TIME)
			{
				if (x < simonX)
				{
					nx = 1;
				}
				else
				{
					nx = -1;
				}

				SetState(RAVEN_STATE_JUMP);
			}
			*/
			
		}

		if (!isStickToGround)
			vy += SIMON_GRAVITY * dt;

		// No collision occured, proceed normally
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

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;

			for (int i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<Ground*>(e->obj))
				{
					// Da cham dat
					// Khong va cham theo phuong ngang
					if (e->ny < 0 || e->nx != 0)
					{
						// Xét va chạm cứng
						SetState(RAVEN_STATE_IDLE);
						isStickToGround = true;
						idleCast = GetTickCount();
					}
				}
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void Raven::Render()
{
	if (!isDeadth && isEnable) {
		int posX = x, posY = y;
		int ani = 0;

		switch (state)
		{
		case RAVEN_STATE_IDLE:
			if (nx > 0)
			{
				ani = RAVEN_ANI_IDLE_RIGHT;
			}
			else
			{
				ani = RAVEN_ANI_IDLE_LEFT;
			}
			break;
		case RAVEN_STATE_JUMP:
			if (nx > 0)
			{
				ani = RAVEN_ANI_JUMP_RIGHT;
		
			}
			else
			{
				ani = RAVEN_ANI_JUMP_LEFT;
			}
			break;
		}

		animation_set->at(ani)->Render(posX, posY);
		RenderBoundingBox();
	}
	Enemy::Render();
}

void Raven::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDeadth && isEnable) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		left = x;
		top = y;
		right = x + RAVEN_BBOX_WIDTH;
		bottom = y + RAVEN_BBOX_HEIGHT;
	}
}

void Raven::SetState(int state)
{
	Enemy::SetState(state);

	switch (state)
	{
	case RAVEN_STATE_IDLE:
		isIdle = true;
		vx = 0;
		vy = 0;
		break;
	case RAVEN_STATE_JUMP:
		vy = -(rand() % 1 + 2) * 0.1f;
		//vy = -0.05f;

		vx = (rand() % 1 + 1) * 0.1f;
		if (nx < 0)
			vx = -vx;

		break;
	}
}
