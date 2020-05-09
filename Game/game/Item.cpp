#include <time.h>
#include "Item.h"
#include "Define.h"
#include "Brick.h"
#include "BoundingMap.h"

Item::Item()
{
	isDeadth = false;
	isEnable = false;
	TimeDisplayMax = ITEM_TIMEDISPLAYMAX;
	RandomType();
	Init();
}

Item::Item(int type)
{
	isDeadth = false;
	isEnable = false;
	typeItem = type;
	TimeDisplayMax = ITEM_TIMEDISPLAYMAX;
	Init();
}

Item::~Item()
{
}

void Item::RandomType()
{
	srand(time(0));
	int percent = rand() % 100;

	if (percent < 90)
		RandomItem();
	else
		RandomWeapon();
}

void Item::RandomItem()
{
	int percent = rand() % 100;

	if (percent > 60)
	{
		typeItem = ITEM_MORNINGSTAR;
	}
	else if (percent < 60)
	{
		typeItem = ITEM_HEART;
	}
}

void Item::RandomWeapon()
{
	int percent = rand() % 100;

	if (percent < 40)
	{
		typeItem = ITEM_AXE;
	}
	else if (percent < 80)
	{
		typeItem = ITEM_CROSS;
	}
	else if (percent < 90)
	{
		typeItem = ITEM_HOLY_WATER;
	}
	else if (percent < 95)
	{
		typeItem = ITEM_DAGGER;
	}
	else
	{
		typeItem = ITEM_STOP_WATCH;
	}
}

void Item::Init()
{
	isGround = false;
	vy = 0;

	switch (typeItem)
	{
	case ITEM_MORNINGSTAR:
		this->width = 32;
		this->height = 32;
		break;
	case ITEM_HEART:
		this->width = 24;
		this->height = 20;
		break;
	}
}

void Item::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDeadth)
	{
		if (!isEnable)
		{
			left = x;
			top = y;
			right = x + width;
			bottom = y + height;
		}
		else {
			switch (typeItem)
			{
			case ITEM_MORNINGSTAR:
				left = x;
				top = y;
				right = x + 16;
				bottom = y + 16;
				break;
			case ITEM_HEART:
				left = x;
				top = y;
				right = x + 12;
				bottom = y + 10;
			case ITEM_SMALL_HEART:
				left = x;
				top = y;
				right = x + 8;
				bottom = y + 8;
				break;
			case ITEM_KNIFE:
				left = x;
				top = y;
				right = x + 16;
				bottom = y + 9;
				break;
			case ITEM_BOOMERANG:
				left = x;
				top = y;
				right = x + 15;
				bottom = y + 14;
				break;
			default:
				break;
			}
		}
	}
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDeadth && isEnable)
	{
		TimeDisplayed += dt;
		if (TimeDisplayed >= TimeDisplayMax)
		{
			this->isDeadth = true;
			this->isEnable = false;
			TimeDisplayed = 0;
			return;
		}

		CGameObject::Update(dt, coObjects);

		if (typeItem != ITEM_SMALL_HEART) {
			vy += SIMON_GRAVITY * dt;
		}
		else {
			vy = SIMON_GRAVITY * dt * 2;
			if (!isGround) {
				DWORD now = GetTickCount();
				int temp = 300;
				if (isFirstTime) {
					//temp = temp / 2;
				}

				if (now - timeStartEnable >= temp) {
					if (isFirstTime) {
						isFirstTime = false;
					}
					if (nx == 1) {
						vx = -SIMON_WALKING_SPEED;
						nx = -1;
					}
					else {
						vx = SIMON_WALKING_SPEED;
						nx = 1;
					}

					timeStartEnable = now;
				}
				else {
					if (nx == 1) {
						vx = SIMON_WALKING_SPEED;
					}
					else {
						vx = -SIMON_WALKING_SPEED;
					}
				}
			}
			else {
				vx = 0;
			}
		}

	
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		/*if (this->state == ITEM_STATE_UP)
		{
			vy += -0.00100f;
			if (vy <= -0.118f)
				this->SetState(ITEM_STATE_IDLE);
		}*/

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

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<BoundingMap*>(e->obj))
				{
					if (e->ny < 0)
					{
						x += min_tx * dx + nx * 0.4f;
						y += min_ty * dy + ny * 0.4f;

						if (nx != 0) vx = 0;
						if (ny != 0) vy = 0;
						isGround = true;

					}
				}

			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void Item::Render()
{
	if (isEnable) {
		animation_set->at(typeItem)->Render(x, y);
		//RenderBoundingBox();
	}
}

void Item::TurnOnTimeStartEnable()
{
	timeStartEnable = GetTickCount();
	nx = 1;
	vx = SIMON_WALKING_SPEED;
	vy = SIMON_GRAVITY * dt * 2;
	isFirstTime = true;
}