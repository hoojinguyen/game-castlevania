#include "MorningStar.h"
#include "Game.h"
#include "Utils.h"
#include "Define.h"

#include "Torch.h"
#include "Candle.h"
#include "Item.h"
#include "Enemy.h"

MorningStar::MorningStar()
{
	damage = 1;
	level = MORNINGSTAR_LEVEL_1;
	indexAni = 0;
}

MorningStar::~MorningStar()
{
}

int MorningStar::GetCurrentFrame()
{
	ani = animation_set->at(indexAni);
	return ani->GetCurrentFrame();
}

void MorningStar::SetPosition(float x, float y, bool isSitting)
{
	if (isSitting)
	{
		y += MORNINGSTAR_DELTA_POSITION_Y;
	}
	CGameObject::SetPosition(x, y);
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

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == MORNINGSTAR_STATE_HIT && isEnable)
	{
		CGameObject::Update(dt);

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);

			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
			{
				if (dynamic_cast<Enemy*>(coObjects->at(i))) {

					Enemy* enemy = dynamic_cast<Enemy*>(coObjects->at(i));

					if ((coObjects->at(i))->nx != 0)
					{
						if (enemy->isEnable != false) {
							enemy->GetCollisionEffect()->SetEnable(true);
							enemy->SetHP(enemy->GetHP() - this->damage);
							this->isEnable = false;
							ResetAnimation();
						}
					}
				}
				else if (dynamic_cast<Item*>(coObjects->at(i))) {
					Item* item = dynamic_cast<Item*>(coObjects->at(i));
					if (!item->GetDeadth() && !item->GetEnable()) {
						item->SetEnable(true);
						if (item->GetTypeItem() == ITEM_SMALL_HEART) {
							item->TurnOnTimeStartEnable();
						}
					}
					
				}
				else if (dynamic_cast<Torch*>(coObjects->at(i))) {
					Torch* torch = dynamic_cast<Torch*>(coObjects->at(i));
					if (torch->isEnable) {
						torch->GetCollisionEffect()->SetEnable(true);
						torch->GetDeadEffect()->SetEnable(true);
						torch->isEnable = false;
						torch->isDeadth = true;
					}
				}
				else if (dynamic_cast<Candle*>(coObjects->at(i))) {
					Candle* candle = dynamic_cast<Candle*>(coObjects->at(i));
					if (candle->isEnable) {
						candle->GetCollisionEffect()->SetEnable(true);
						candle->GetDeadEffect()->SetEnable(true);
						candle->isEnable = false;
						candle->isDeadth = true;
					}
				}
			}
		}
	}
}

void MorningStar::Render(bool isRight)
{
	if (isEnable)
	{
		float posX = x, posY = y;

		switch (level)
		{
		case MORNINGSTAR_LEVEL_1:
			if (isRight)
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
			if (isRight)
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
			if (isRight)
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
			if (isRight)
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
			if (isRight)
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
			//RenderBoundingBox();
		}

	}
}

void MorningStar::Render()
{

}

void MorningStar::ResetAnimation()
{
	for (int i = 0; i < 12; i++)
	{
		ResetAni(i);
	}
}


