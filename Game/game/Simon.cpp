#include "Simon.h"
#include "Define.h"
#include "Torch.h"
#include "Item.h"
#include "Game.h"
#include "Candle.h"
#include "Utils.h"
#include "ObjectHidden.h"
#include "BoundingMap.h"

Simon* Simon::__instance = NULL;

Simon::Simon(float X ,float Y)
{
	level = 0;
	hp = SIMON_HP;
	energy = 5;
	score = 0;
	life = 3;

	untouchable = 0;
	untouchable_start = 0;

	isAttacking = false;
	isJumping = false;
	isSitting = false;
	isRunning = false;

	timeAttackStart = 0;

	morningStar = new MorningStar();

	state = SIMON_STATE_IDLE;

	checkPointX = X;
	checkPointY = Y;
	x = X;
	y = Y;
}

Simon* Simon::GetInstance()
{
	if (__instance == NULL) __instance = new Simon(0, 0);
	return __instance;
}

void Simon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(checkPointX, checkPointY);
	SetSpeed(0, 0);
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);
	DWORD currentTime = GetTickCount();
	switch (state)
	{
	case SIMON_STATE_WALK_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALK_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		isJumping = true;
		isGround = false;
		vy = -SIMON_JUMP_SPEED_Y;
	case SIMON_STATE_IDLE:
		isSitting = false;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_SIT_DOWN:
		vx = 0;
		isSitting = true;
		break;
	case SIMON_STATE_ATTACKING:
		vx = 0;
		isAttacking = true;
		timeAttackStart = currentTime;
		morningStar->SetEnable(true);
		morningStar->SetState(MORNINGSTAR_STATE_PREPARE);
		break;
	}
}

int Simon::GetLevelMorningStar()
{
	return morningStar->GetLevel();
}

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDead)
	{
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else
	{
		int boxWidth = SIMON_BBOX_WIDTH;
		int boxHeight = SIMON_BBOX_HEIGHT;
		//switch (state)
		//{
		//case SIMON_STATE_JUMP:
		//	boxWidth = SIMON_JUMP_BBOX_WIDTH;
		//	boxHeight = SIMON_JUMP_BBOX_HEIGHT;
		//	break;
		//case SIMON_STATE_RUN_JUMP:
		//	boxWidth = SIMON_JUMP_BBOX_WIDTH;
		//	boxHeight = SIMON_JUMP_BBOX_HEIGHT;
		//	break;
		//}
		left = x;
		top = y;
		right = left + boxWidth;
		bottom = top + boxHeight;
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD now = GetTickCount();
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	if (isAttacking)
	{
		morningStar->SetPosition(x, y, isSitting);
		morningStar->Update(dt, coObjects);
		if (now - timeAttackStart > (SIMON_ATTACK_TIME - 100))
		{
			morningStar->SetState(MORNINGSTAR_STATE_HIT);
		}
		if (now - timeAttackStart > SIMON_ATTACK_TIME)
		{
			timeAttackStart = 0;
			isAttacking = false;
			morningStar->ResetAnimation();
			morningStar->SetEnable(false);
			ResetAnimationAttacking();
		}
	}

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Item*>(coObjects->at(i))) {
			Item* item = dynamic_cast<Item*>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			item->GetBoundingBox(l2, t2, r2, b2);

			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
			{
				if (!item->GetDead() && item->GetEnable()) {
					item->SetDead(true);
					item->SetEnable(false);
				}
			}
		}
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (dynamic_cast<Torch*>(e->obj) || dynamic_cast<Candle*>(e->obj))
		{
			coEvents.erase(coEvents.begin() + i);
		}
	}

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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Item*>(e->obj))
			{
				Item* item = dynamic_cast<Item*>(e->obj);
				if (!item->GetDead() && item->GetEnable())
				{
					switch (item->GetTypeItem())
					{
					case ITEM_MORNINGSTAR:
						if (morningStar->GetLevel() < MORNINGSTAR_LEVEL_3)
						{
							morningStar->SetLevel(morningStar->GetLevel() + 1);
						}
						break;
					case ITEM_SMALL_HEART:
						energy += 1;
						break;
					case ITEM_HEART:
						energy += 5;
						break;
					}
					item->SetDead(true);
					item->SetEnable(false);
				}
			}
			else if (dynamic_cast<CObjectHidden*>(e->obj))
			{
				CObjectHidden* p = dynamic_cast<CObjectHidden*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}

			if (dynamic_cast<BoundingMap*>(e->obj))
			{
				BoundingMap* boundingMap = dynamic_cast<BoundingMap*>(e->obj);

				// block 
				if (e->ny < 0)
				{
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;

					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}

				if (isJumping)
				{
					//SetState(SIMON_STATE_IDLE);
					isJumping = false;
				}
			}
			else {
				x += dx;
				if (ny < 0)
					y += dy + ny * 0.7f;
				else if (ny > 0)
					y += dy + ny * -0.7f;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::Render()
{
	int ani = 0;
	float posX = x, posY = y;
	if (state == SIMON_STATE_DIE)
	{
		if (nx > 0) ani = SIMON_ANI_DEATH_RIGHT;
		else ani = SIMON_ANI_DEATH_LEFT;
	}
	else
	{
		if (isSitting) {
			if (isAttacking)
			{
				if (nx > 0) ani = SIMON_ANI_ATTACKING_SIT_RIGHT;
				else ani = SIMON_ANI_ATTACKING_SIT_LEFT;
			}
			else if (nx != 0)
			{
				if (nx > 0) ani = SIMON_ANI_SIT_DOWN_RIGHT;
				else ani = SIMON_ANI_SIT_DOWN_LEFT;
			}
			posY = y + 8;
		}
		else if (isJumping) {
			if (isAttacking)
			{
				if (nx > 0) ani = SIMON_ANI_ATTACKING_RIGHT;
				else ani = SIMON_ANI_ATTACKING_LEFT;
			}
			else if (nx != 0)
			{
				if (nx > 0) ani = SIMON_ANI_SIT_DOWN_RIGHT;
				else ani = SIMON_ANI_SIT_DOWN_LEFT;
			}
		}
		else {
			if (isAttacking)
			{
				if (nx > 0) ani = SIMON_ANI_ATTACKING_RIGHT;
				else ani = SIMON_ANI_ATTACKING_LEFT;
			}
			else {
				if (vx == 0)
				{
					if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
					else ani = SIMON_ANI_IDLE_LEFT;
				}
				else
				{
					if (vx > 0)
						ani = SIMON_ANI_WALKING_RIGHT;
					else ani = SIMON_ANI_WALKING_LEFT;
				}
			}
		}

	}

	if (isAttacking)
	{
		morningStar->SetPosition(x, y, isSitting);
		morningStar->Render(nx > 0);
	}

	int alpha = 255;
	if (untouchable) alpha = 128;
	animation_set->at(ani)->Render(posX, posY, alpha);

	RenderBoundingBox();
}

void Simon::ResetCheckpoint()
{
	x = checkPointX;
	y = checkPointY;
	hp = SIMON_MAX_HP;
}

void Simon::ResetAnimationAttacking()
{
	ResetAni(SIMON_ANI_ATTACKING_RIGHT);
	ResetAni(SIMON_ANI_ATTACKING_LEFT);

	ResetAni(SIMON_ANI_ATTACKING_SIT_RIGHT);
	ResetAni(SIMON_ANI_ATTACKING_SIT_LEFT);
}

void Simon::SetAnimationSetMorningStar(LPANIMATION_SET ani_set)
{
	morningStar->SetAnimationSet(ani_set);
}
