#include "MorningStar.h"
#include "Define.h"
#include "Torch.h"
#include "Item.h"
#include "Game.h"
#include "Utils.h"

MorningStar::MorningStar()
{
	damage = 1;
	level = MORNINGSTAR_LEVEL_1;
	indexAni = 0;
}

MorningStar::~MorningStar()
{
}


void MorningStar::Render()
{
}

void MorningStar::Render(bool IsRight)
{
	if (isEnable)
	{
		float posX = x, posY = y;

		switch (level)
		{
		case MORNINGSTAR_LEVEL_1:
			if (IsRight)
			{
				if (state == MORNINGSTAR_STATE_PREPARE)
				{
					indexAni = MORNINGSTAR_LEVEL_1_ANI_PREPARE_RIGHT;
				}
				else {
					indexAni = MORNINGSTAR_LEVEL_1_ANI_RIGHT;
				}
			}
			else
			{
				if (state == MORNINGSTAR_STATE_PREPARE)
				{
					indexAni = MORNINGSTAR_LEVEL_1_ANI_PREPARE_LEFT;
				}
				else {
					indexAni = MORNINGSTAR_LEVEL_1_ANI_LEFT;
				}
			}
			break;
		case MORNINGSTAR_LEVEL_2:
			if (IsRight)
			{
				if (state == MORNINGSTAR_STATE_PREPARE)
				{
					indexAni = MORNINGSTAR_LEVEL_2_ANI_PREPARE_RIGHT;
				}
				else {
					indexAni = MORNINGSTAR_LEVEL_2_ANI_RIGHT;
				}
			}
			else
			{
				if (state == MORNINGSTAR_STATE_PREPARE)
				{
					indexAni = MORNINGSTAR_LEVEL_2_ANI_PREPARE_LEFT;
				}
				else {
					indexAni = MORNINGSTAR_LEVEL_2_ANI_LEFT;
				}
			}
			break;
		case MORNINGSTAR_LEVEL_3:
			if (IsRight)
			{
				if (state == MORNINGSTAR_STATE_PREPARE)
				{
					indexAni = MORNINGSTAR_LEVEL_3_ANI_PREPARE_RIGHT;
				}
				else {
					indexAni = MORNINGSTAR_LEVEL_3_ANI_RIGHT;
				}
			}
			else
			{
				if (state == MORNINGSTAR_STATE_PREPARE)
				{
					indexAni = MORNINGSTAR_LEVEL_3_ANI_PREPARE_LEFT;
				}
				else {
					indexAni = MORNINGSTAR_LEVEL_3_ANI_LEFT;
				}
			}
			break;
		}

		if (state != MORNINGSTAR_STATE_PREPARE)
		{
			if (IsRight)
			{
				posX = x + SIMON_BBOX_WIDTH + MORNINGSTAR_DELTA_X_RIGHT;
			}
			else {
				if (level == MORNINGSTAR_LEVEL_1)
				{
					posX = x - MORNINGSTAR_DELTA_X_LEFT - MORNINGSTAR_LEVEL_1_BBOX_WIDTH;
				}
				else if (level == MORNINGSTAR_LEVEL_2)
				{
					posX = x - MORNINGSTAR_DELTA_X_LEFT - MORNINGSTAR_LEVEL_2_BBOX_WIDTH;
				}
				else {
					posX = x - MORNINGSTAR_DELTA_X_LEFT - MORNINGSTAR_LEVEL_3_BBOX_WIDTH;
				}

			}
			if (level == MORNINGSTAR_LEVEL_1)
			{
				posY = y + MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT - 2;
			}
			else if (level == MORNINGSTAR_LEVEL_2)
			{
				posY = y + MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT - 1;
			}
			else {
				posY = y + MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT;
			}

		}
		else {
			if (IsRight)
			{
				posX = x - SIMON_BBOX_WIDTH;
			}
			else {
				posX = x + SIMON_BBOX_WIDTH;
			}
		}

		animation_set->at(indexAni)->Render(posX, posY);
		if (state == MORNINGSTAR_STATE_HIT)
		{
			RenderBoundingBox();
		}

	}
}

void MorningStar::SetPosition(float x, float y, bool isSitting)
{
	if (isSitting)
	{
		y += MORNINGSTAR_DELTA_POSITION_Y;
	}
	CGameObject::SetPosition(x, y);
}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == MORNINGSTAR_STATE_HIT)
	{
		CGameObject::Update(dt);

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);

			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
			{
				if (dynamic_cast<Item*>(coObjects->at(i))) {
					Item* item = dynamic_cast<Item*>(coObjects->at(i));

					if (!item->GetDead() && !item->GetEnable()) {
						item->SetEnable(true);
					}
				}
				else if (dynamic_cast<Torch*>(coObjects->at(i))) {
					Torch* torch = dynamic_cast<Torch*>(coObjects->at(i));

					if (torch->isEnable) {
						torch->GetCollisionEffect()->SetEnable(true);
						torch->GetDeadEffect()->SetEnable(true);
						torch->isEnable = false;
						torch->isDead = true;
					}
				}
			}
		}
	}
}

void MorningStar::ResetAnimation()
{
	ResetAni(0);
	ResetAni(1);
	ResetAni(2);
	ResetAni(3);
	ResetAni(4);
	ResetAni(5);
	ResetAni(6);
	ResetAni(7);
	ResetAni(8);
	ResetAni(9);
	ResetAni(10);
	ResetAni(11);
}

int MorningStar::GetCurrentFrame()
{
	ani = animation_set->at(indexAni);
	return ani->GetCurrentFrame();
}

void MorningStar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (indexAni)
	{
	case MORNINGSTAR_LEVEL_1_ANI_LEFT:
		left = x - MORNINGSTAR_DELTA_X_LEFT - MORNINGSTAR_LEVEL_1_BBOX_WIDTH;
		top = y + MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT;
		right = left + MORNINGSTAR_LEVEL_1_BBOX_WIDTH;
		bottom = top + MORNINGSTAR_LEVEL_1_BBOX_HEIGHT;
		break;
	case MORNINGSTAR_LEVEL_1_ANI_RIGHT:
		left = x + SIMON_BBOX_WIDTH + MORNINGSTAR_DELTA_X_RIGHT;
		top = y + MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT;
		right = left + MORNINGSTAR_LEVEL_1_BBOX_WIDTH;
		bottom = top + MORNINGSTAR_LEVEL_1_BBOX_HEIGHT;
		break;
	case MORNINGSTAR_LEVEL_2_ANI_LEFT:
		left = x - MORNINGSTAR_DELTA_X_LEFT - MORNINGSTAR_LEVEL_2_BBOX_WIDTH;
		top = y + MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT;
		right = left + MORNINGSTAR_LEVEL_2_BBOX_WIDTH;
		bottom = top + MORNINGSTAR_LEVEL_2_BBOX_HEIGHT;
		break;
	case MORNINGSTAR_LEVEL_2_ANI_RIGHT:
		left = x + SIMON_BBOX_WIDTH + MORNINGSTAR_DELTA_X_RIGHT;
		top = y + MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT;
		right = left + MORNINGSTAR_LEVEL_2_BBOX_WIDTH;
		bottom = top + MORNINGSTAR_LEVEL_2_BBOX_HEIGHT;
		break;
	case MORNINGSTAR_LEVEL_3_ANI_LEFT:
		left = x - MORNINGSTAR_DELTA_X_LEFT - MORNINGSTAR_LEVEL_3_BBOX_WIDTH;
		top = y + MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT;
		right = left + MORNINGSTAR_LEVEL_3_BBOX_WIDTH;
		bottom = top + MORNINGSTAR_LEVEL_3_BBOX_HEIGHT;
		break;
	case MORNINGSTAR_LEVEL_3_ANI_RIGHT:
		left = x + SIMON_BBOX_WIDTH + MORNINGSTAR_DELTA_X_RIGHT;
		top = y + MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT;
		right = left + MORNINGSTAR_LEVEL_3_BBOX_WIDTH;
		bottom = top + MORNINGSTAR_LEVEL_3_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}

