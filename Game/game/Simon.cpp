#include "Simon.h"
#include "Define.h"
#include "Torch.h"
#include "Item.h"
#include "Game.h"
#include "Candle.h"
#include "BrickAni.h"
#include "Utils.h"
#include "ObjectHidden.h"
#include "BoundingMap.h"
#include "Ground.h"
#include "Wall.h"
#include "StairBottom.h"
#include "StairTop.h"
#include "Enemy.h"
#include "VampireBat.h"


using namespace std;

Simon* Simon::__instance = NULL;

Simon::Simon()
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
	isWall = false;

	isFreeze = false;

	timeFreezeStart = 0;
	timeAttackStart = 0;

	DoCaoDiDuoc = 0;
	_IsFirstOnStair = false;

	state = SIMON_STATE_IDLE;

	morningStar = new MorningStar();

	for (int i = 0; i < 3; i++)
	{
		daggers[i] = new Dagger();
		boomerangs[i] = new Boomerang();
		axes[i] = new Axe();
		fireBombs[i] = new FireBomb();
		stopwatchs[i] = new Stopwatch();
		weapons[i] = daggers[i];
	}
}

Simon* Simon::GetInstance()
{
	if (__instance == NULL) __instance = new Simon();
	return __instance;
}

void Simon::SetTypeOfWeapon(int item)
{
	for (int i = 0; i < 3; i++)
	{
		switch (item)
		{

		case ITEM_HOLY_WATER:
			weapons[i] = fireBombs[i];
			typeWeaponCollect = item;
			break;
		case ITEM_AXE:
			weapons[i] = axes[i];
			typeWeaponCollect = item;
			break;
		case ITEM_DAGGER:
			weapons[i] = daggers[i];
			typeWeaponCollect = item;
			break;
		case ITEM_BOOMERANG:
			weapons[i] = boomerangs[i];
			typeWeaponCollect = item;
			break;
		case ITEM_STOP_WATCH:
			weapons[i] = stopwatchs[i];
			typeWeaponCollect = item;
			break;
		default:
			break;
		}
	}
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);
	DWORD currentTime = GetTickCount();
	switch (state)
	{
	case SIMON_STATE_WALK_RIGHT:
	{
		isRunning = true;
		vx = SIMON_WALKING_SPEED;
		nx = 1;
	}
	break;
	case SIMON_STATE_WALK_LEFT:
	{
		isRunning = true;
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
	}
	break;
	case SIMON_STATE_JUMP:
		/*
		
		if (!isOnStair && !isUpStair && !isDownStair) {
			isJumping = true;
			isGround = false;
			vy = -SIMON_JUMP_SPEED_Y;
		}
		*/

		isJumping = true;
		isGround = false;
		vy = -SIMON_JUMP_SPEED_Y;
	case SIMON_STATE_IDLE:
		isSitting = false;
		isRunning = false;
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vx = 0;
		vy = SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_SIT_DOWN:
		vx = 0;
		isSitting = true;
		break;
	case SIMON_STATE_CLIMB_STAIR_UP:
		/*
		if (!isOnStair && !isSitting) {
			x = xStair - 6;
		}
		if (canClimbDownStair) {
			isOnStair = false;
			isUpStair = false;
			isDownStair = false;
			y -= 15;
			//y -= 5;
			vx = 0;
		}
		else {
			vx = SIMON_WALKING_SPEED / 2;
			vy = -SIMON_WALKING_SPEED / 2;
			isOnStair = true;
			isUpStair = true;
			isDownStair = false;
		}
		break;
		*/
		if (!isOnStair) {
			if (directionStair > 0) {
				x = xStair - 6;
			}
			else {
				x = xStair + 5;
				//y = posYStair + 7 - SIMON_BBOX_HEIGHT;
			}
			isOnStair = true;
			isUpStair = true;
			isDownStair = false;
			_IsFirstOnStair = true;
		}
		else {
			_IsFirstOnStair = false;
			if (canClimbDownStair) {
				isOnStair = false;
				isUpStair = false;
				isDownStair = false;
				y -= 2;
				vx = 0;
			}
			else {
				if (directionStair > 0) {
					vx = SIMON_JUMP_SPEED_STAIR;
				}
				else {
					vx = -SIMON_JUMP_SPEED_STAIR;
				}
				vy = -SIMON_JUMP_SPEED_STAIR;
				isOnStair = true;
				isUpStair = true;
				isDownStair = false;
			}
		}
		break;
	case SIMON_STATE_CLIMB_STAIR_DOWN:
		/*
		if (!isOnStair) {
			x = xStair;
			y += 8;
		}
		vx = -SIMON_WALKING_SPEED / 2;
		vy = SIMON_WALKING_SPEED / 2;
		isOnStair = true;
		isUpStair = false;
		isDownStair = true;
		break;
		*/

		if (!isOnStair) {
			if (directionStair > 0) {
				x = xStair;
				y += 8;
			}
			else {
				x = xStair;
				y = yStair;
			}

			isOnStair = true;
			isUpStair = false;
			isDownStair = true;
			_IsFirstOnStair = true;
		}
		else {
			if (directionStair > 0) {
				vx = -SIMON_JUMP_SPEED_STAIR;
			}
			else {
				vx = SIMON_JUMP_SPEED_STAIR;
			}
			vy = SIMON_JUMP_SPEED_STAIR;
			isOnStair = true;
			isUpStair = false;
			isDownStair = true;
			_IsFirstOnStair = false;
		}
		break;

	case SIMON_STATE_ATTACKING:
		if (isJumping) {
			y -= 4;
		}
		vx = 0;
		isAttacking = true;
		timeAttackStart = currentTime;
		morningStar->SetEnable(true);
		morningStar->SetState(MORNINGSTAR_STATE_PREPARE);
		break;
	case SIMON_STATE_HURT:
		isGround = false;
		if (isOnStair) {
			vy = 0;
			vx = 0;
		}
		else
		{
			if (nx > 0)
			{
				vx = -0.03;
			}
			if (nx < 0)
			{
				vx = 0.03;
			}
			vy = -0.2;
		}
		break;
	}
}

int Simon::GetLevelMorningStar()
{
	return morningStar->GetLevel();
}

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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
		int boxWidth = SIMON_BBOX_WIDTH;
		int boxHeight = SIMON_BBOX_HEIGHT;
		if (isJumping && !isAttacking) {
			boxHeight -= 8;
		}

		left = x;
		top = y;

		if (isSitting) {
			boxHeight -= 8;
			top = y + 8;
		}
		right = left + boxWidth;
		bottom = top + boxHeight;
	}
}

void Simon::HandleCollisionSimonWithItem(Item* item, DWORD now)
{
	switch (item->GetTypeItem())
	{
	case ITEM_MORNINGSTAR:
		if (morningStar->GetLevel() < MORNINGSTAR_LEVEL_3)
		{
			morningStar->SetLevel(morningStar->GetLevel() + 1);
			isFreeze = true;
			timeFreezeStart = now; // thời gian đã đóng băng
		}
		break;
	case ITEM_SMALL_HEART:
		energy += 1;
		break;
	case ITEM_LARGE_HEART:
		energy += 5;
		break;
	case ITEM_MONEY_BAG_RED:
		score += 100;
		item->GetMoneyEffect()->SetEnable(true);
		break;
	case ITEM_MONEY_BAG_PURPLE:
		score += 400;
		item->GetMoneyEffect()->SetEnable(true);
		break;
	case ITEM_MONEY_BAG_WHITE:
		score += 700;
		item->GetMoneyEffect()->SetEnable(true);
		break;
	case ITEM_DAGGER:
		SetTypeOfWeapon(ITEM_DAGGER);
		break;
	case ITEM_AXE:
		SetTypeOfWeapon(ITEM_AXE);
		break;
	case ITEM_HOLY_WATER:
		SetTypeOfWeapon(ITEM_HOLY_WATER);
		break;
	case ITEM_BOOMERANG:
		SetTypeOfWeapon(ITEM_BOOMERANG);
		break;
	case ITEM_STOP_WATCH:
		SetTypeOfWeapon(ITEM_STOP_WATCH);
		break;
	case ITEM_BONUSES:
		score += 1000;
		item->GetMoneyEffect()->SetEnable(true);
		break;
	case ITEM_CROWN:
	case ITEM_CHEST:
		score += 2000;
		item->GetMoneyEffect()->SetEnable(true);
		break;
	case ITEM_DOUBLE_SHOT:
		typeShotCollect = ITEM_DOUBLE_SHOT;
		break;
	case ITEM_TRIPLE_SHOT:
		typeShotCollect = ITEM_TRIPLE_SHOT;
		break;
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD now = GetTickCount();
	CGameObject::Update(dt);

	//isWall = false;


	//if (hp <= 0) SetState(SIMON_STATE_DIE);


	// Simple fall down
	if (!isOnStair) {
		vy += SIMON_GRAVITY * dt;
	}
	else {
		if (isUpStair) {
			nx = directionStair;
		}
		else {
			nx = -directionStair;
		}

		DoCaoDiDuoc = DoCaoDiDuoc + abs(vy) * 16.0f;


		if (DoCaoDiDuoc > SIMON_FIXED_LENGTH_STAIR)
		{
			/* fix lỗi mỗi lần đi vượt quá 8px */
			if (nx > 0 && isUpStair) // đi lên bên phải
			{
				x -= (DoCaoDiDuoc - SIMON_FIXED_LENGTH_STAIR);
				y += (DoCaoDiDuoc - SIMON_FIXED_LENGTH_STAIR);
			}
			if (nx < 0 && isUpStair) // đi lên bên trái
			{
				x += (DoCaoDiDuoc - SIMON_FIXED_LENGTH_STAIR);
				y += (DoCaoDiDuoc - SIMON_FIXED_LENGTH_STAIR);
			}
			if (nx < 0 && isDownStair) // đi xuống bên phải
			{
				x -= (DoCaoDiDuoc - SIMON_FIXED_LENGTH_STAIR);
				y -= (DoCaoDiDuoc - SIMON_FIXED_LENGTH_STAIR);
			}
			if (nx > 0 && isDownStair) // đi xuống bên trái
			{
				x += (DoCaoDiDuoc - SIMON_FIXED_LENGTH_STAIR);
				y -= (DoCaoDiDuoc - SIMON_FIXED_LENGTH_STAIR);
			}
			DebugOut(L"DoCaoDiDuoc = %f . dy = %f . y = %f\n", DoCaoDiDuoc, dy, y);
			DoCaoDiDuoc = 0;
		}
		else {
			DebugOut(L"DoCaoDiDuoc = %f . dy = %f . y = %f\n", DoCaoDiDuoc, dy, y);
		}
	}

	// Check xem simon có đang đánh hay ko ??
	if (isAttacking)
	{
		morningStar->SetPosition(x, y, isSitting);
		morningStar->Update(dt, coObjects);
		if (now - timeAttackStart > (SIMON_ATTACK_TIME - 150))
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

	if (isFreeze) {
		if (now - timeFreezeStart > TIME_FREEZE_MAX)
		{
			timeFreezeStart = 0;
			isFreeze = false;
		}
		else {
			vx = 0;
			vy = 0;
			isRunning = false;
		}
	}


	if (canClimbUpStair) {
		canClimbUpStair = false;
	}
	if (canClimbDownStair) {
		canClimbDownStair = false;
	}

	// Kiem tra va cham voi item 
	for (UINT i = 0; i < coObjects->size(); i++)
	{


		if (dynamic_cast<Item*>(coObjects->at(i))) {
			Item* item = dynamic_cast<Item*>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			item->GetBoundingBox(l2, t2, r2, b2);

			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
			{
				if (!item->GetDeadth() && item->GetEnable()) {
					this->HandleCollisionSimonWithItem(item, now);
					item->SetDeadth(true);
					item->SetEnable(false);
				}
			}
		}



		if (dynamic_cast<Enemy*>(coObjects->at(i)))
		{
			Enemy* enemy = dynamic_cast<Enemy*>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);
			if ((CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))) {
				if ((coObjects->at(i))->vx != 0)
				{
					if (untouchable == 0)
					{
						if (enemy->isEnable != false)
						{
							if (hp > 0)
							{
								//isFreeze = true;
								//timeFreezeStart = now; // thời gian đã đóng băng

								hp -= enemy->GetDamage();
								StartUntouchable();
								SetState(SIMON_STATE_HURT);
								StartHurting();
								if (dynamic_cast<VampireBat*>(coObjects->at(i)))
								{
									enemy->SetDeadth(true);
									enemy->SetEnable(false);
									enemy->GetCollisionEffect()->SetEnable(true);
								}

							}
							else
								//SetPosition(xBackup, yBackup);
								SetState(SIMON_STATE_DIE);
						}
					}


				}
			}
		}
		if (dynamic_cast<StairTop*>(coObjects->at(i))) {
			StairTop* item = dynamic_cast<StairTop*>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			item->GetBoundingBox(l2, t2, r2, b2);

			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
			{
				canClimbDownStair = true;
				xStair = item->x;
				yStair = item->y;
				directionStair = item->nx;
			}
		}
		else if (dynamic_cast<StairBottom*>(coObjects->at(i))) {
			StairBottom* item = dynamic_cast<StairBottom*>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			item->GetBoundingBox(l2, t2, r2, b2);

			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
			{
				canClimbUpStair = true;
				xStair = item->x;
				yStair = item->y;
				directionStair = item->nx;
			}
		}
	}

	if (typeWeaponCollect >= ITEM_DAGGER && typeWeaponCollect >= ITEM_STOP_WATCH) {
		for (int i = 0; i < typeShotCollect; i++)
		{
			if (!weapons[i])
				weapons[i] = weapons[0];
			if (weapons[i]->GetEnable())
				weapons[i]->Update(dt, coObjects);
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

	if (isHurt) {
		if (GetTickCount() - hurtable_start > 1000)
		{
			hurtable_start = 0;
			hurtable = 0;
			isHurt = false;
			ResetAnimationHurt();
		}
	}

	if (this->GetState() != SIMON_STATE_SIT_DOWN)
		isSitting = false;

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
		//x += dx;
		//y += dy;

		if (!_IsFirstOnStair) {
			x += dx;
			y += dy;
		}
		else {
			_IsFirstOnStair = false;
		}
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
				if (!item->GetDeadth() && item->GetEnable())
				{
					this->HandleCollisionSimonWithItem(item, now);
					item->SetDeadth(true);
					item->SetEnable(false);
				}
			}
			else if (dynamic_cast<BrickAni*>(e->obj)) {
				if (e->ny < 0)
				{
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;

					if (ny != 0) vy = 0;
					vx = e->obj->vx;
				}
				if (isJumping)
				{
					y -= 8;
					isJumping = false;
				}
			}
			else if (dynamic_cast<Ground*>(e->obj))
			{
				if (!isOnStair || isDownStair) {
					Ground* ground = dynamic_cast<Ground*>(e->obj);
					// block 
					if (e->ny < 0 || e->nx != 0)
					{
						x += min_tx * dx + nx * 0.4f;
						y += min_ty * dy + ny * 0.4f;

						if (nx != 0) vx = 0;
						if (ny != 0) vy = 0;

						if (isJumping)
						{
							y -= 8;
							isJumping = false;
						}

					}
					else {
						x += dx;
						y += dy;
					}

					if (isOnStair) {
						if (canClimbUpStair) {
							isOnStair = false;
							isUpStair = false;
							isDownStair = false;
							vx = 0;
						}
					}
					if (isHurt) {
						hurtable_start = 0;
						hurtable = 0;
						isHurt = false;
						vx = 0;
						ResetAnimationHurt();
					}
				}
				else {
					/*
					x += dx;
					if (ny < 0)
						y += dy + ny * 0.7f;
					else if (ny > 0)
						y += dy + ny * -0.7f;	
					*/

					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;

					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;

				}

			}
			else if (dynamic_cast<Wall*>(e->obj))
			{
				/*
				Wall* wall = dynamic_cast<Wall*>(e->obj);
				isWall = true;
				*/

				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			else if (dynamic_cast<BoundingMap*>(e->obj)) {
				/*if (e->nx != 0)
				{

				}*/
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				/*if (IsJump)
				{
					y -= 8;
					IsJump = false;
				}*/
			}

			/*
			
			else if (dynamic_cast<BoundingMap*>(e->obj))
			{
			if (!isOnStair || isDownStair) {
				BoundingMap* wall = dynamic_cast<BoundingMap*>(e->obj);
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
					y -= 8;
					isJumping = false;
				}

				if (isOnStair) {
					if (canClimbUpStair) {
						isOnStair = false;
						isUpStair = false;
						isDownStair = false;
					}
				}
				if (isHurt) {
					hurtable_start = 0;
					hurtable = 0;
					isHurt = false;
					vx = 0;
					ResetAnimationHurt();
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
			*/
			else if (dynamic_cast<StairBottom*>(e->obj))
			{
				x += dx;
				if (e->ny < 0)
				{
					y += dy + ny * -0.7f;
				}
				else if (e->nx != 0)
				{
					if (ny < 0)
						y += dy + ny * 0.7f;
					else if (ny > 0)
						y += dy + ny * -0.7f;
				}
			}
			else if (dynamic_cast<CObjectHidden*>(e->obj))
			{
				CObjectHidden* p = dynamic_cast<CObjectHidden*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				return;
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
		if (isHurt) {
			if (nx > 0) ani = SIMON_ANI_HURT_RIGHT;
			else ani = SIMON_ANI_HURT_LEFT;
		}
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
		else if (isUpStair) {
			if (isAttacking)
			{
				if (nx > 0) ani = SIMON_ANI_ATTACKING_UP_STAIR_RIGHT; 
				 else ani = SIMON_ANI_ATTACKING_UP_STAIR_LEFT;
			}
			else {
				if (vx == 0)
				{
					if (nx > 0) ani = SIMON_ANI_IDLE_STAIR_UP_RIGHT;
					else ani = SIMON_ANI_IDLE_STAIR_UP_LEFT;
				}
				else
				{
					if (vx > 0)	ani = SIMON_ANI_CIMB_STAIR_UP_RIGHT;
					else ani = SIMON_ANI_CIMB_STAIR_UP_LEFT;
				}
			}
		}
		else if (isDownStair) {
			if (isAttacking)
			{
				if (nx > 0) ani = SIMON_ANI_ATTACKING_DOWN_STAIR_RIGHT;
				else ani = SIMON_ANI_ATTACKING_DOWN_STAIR_LEFT;
			}
			else {
				if (vx == 0)
				{
					if (nx > 0) ani = SIMON_ANI_IDLE_STAIR_DOWN_RIGHT;
					else ani = SIMON_ANI_IDLE_STAIR_DOWN_LEFT;
				}
				else
				{
					if (vx > 0) ani = SIMON_ANI_CIMB_STAIR_DOWN_RIGHT;
					else ani = SIMON_ANI_CIMB_STAIR_DOWN_LEFT;
				}
			}
		}
		else {
			if (isAttacking)
			{
				if (nx > 0) ani = SIMON_ANI_ATTACKING_RIGHT;
				else ani = SIMON_ANI_ATTACKING_LEFT;
			}
			else {
				if (!isRunning)
				{
					if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
					else ani = SIMON_ANI_IDLE_LEFT;
				}
				else
				{
					if (vx > 0) {
						ani = SIMON_ANI_WALKING_RIGHT;
					}
					else {
						ani = SIMON_ANI_WALKING_LEFT;
					}
				}
				/*
				
				if (vx == 0)
				{
					if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
					else ani = SIMON_ANI_IDLE_LEFT;
				}
				else
				{
					if (vx > 0) ani = SIMON_ANI_WALKING_RIGHT;
					else ani = SIMON_ANI_WALKING_LEFT;
				}
				*/
			}
		}

	}

	if (isAttacking)
	{
		bool isRight = nx > 0;
		morningStar->SetPosition(this->x, this->y, isSitting);
		morningStar->Render(isRight);
	}

	if (typeWeaponCollect >= ITEM_DAGGER && typeWeaponCollect >= ITEM_STOP_WATCH) {
		for (int i = 0; i < typeShotCollect; i++)
		{
			if (weapons[i]->GetEnable())
				weapons[i]->Render();
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;
	if (isFreeze)
	{
		animation_set->at(ani)->Render(posX, posY, alpha, rand() % 256, rand() % 256, rand() % 256);
	}
	else {
		animation_set->at(ani)->Render(posX, posY, alpha);
	}
	
	//RenderBoundingBox();
}

void Simon::Hurted(int damage)
{
	if (hp > 0)
	{
		hp -= damage;
		StartUntouchable();
		SetState(SIMON_STATE_HURT);
		StartHurting();
	}
	else
		SetState(SIMON_STATE_DIE);
}

void Simon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(xBackup, yBackup);
	SetSpeed(0, 0);
}

void Simon::ResetBackupSimon()
{
	this->x = xBackup;
	this->y = yBackup;
	this->hp = SIMON_MAX_HP;
}

void Simon::ResetAnimationAttacking()
{
	ResetAni(SIMON_ANI_ATTACKING_RIGHT);
	ResetAni(SIMON_ANI_ATTACKING_LEFT);

	ResetAni(SIMON_ANI_ATTACKING_SIT_RIGHT);
	ResetAni(SIMON_ANI_ATTACKING_SIT_LEFT);

	ResetAni(SIMON_ANI_ATTACKING_UP_STAIR_RIGHT);
	ResetAni(SIMON_ANI_ATTACKING_UP_STAIR_LEFT);

	ResetAni(SIMON_ANI_ATTACKING_DOWN_STAIR_RIGHT);
	ResetAni(SIMON_ANI_ATTACKING_DOWN_STAIR_LEFT);
}

void Simon::ResetAnimationHurt()
{
	ResetAni(SIMON_ANI_HURT_LEFT);
	ResetAni(SIMON_ANI_HURT_RIGHT);
}

void Simon::SetAnimationSetMorningStar(LPANIMATION_SET ani_set)
{
	morningStar->SetAnimationSet(ani_set);
}

void Simon::SetPosition(float x, float y)
{

	this->x = x;
	this->y = y;
}

void Simon::SetPositionBackup(float xBackup, float yBackup) {
	this->xBackup = xBackup;
	this->yBackup = yBackup;
}


// Load Simon 
#include <iostream>
#include <fstream>

void Simon::Load(LPCWSTR simonFile)
{
	DebugOut(L"[INFO] Start loading simon resources from : %s \n", simonFile);

	ifstream f;
	f.open(simonFile);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines
		if (line[0] == '/' && line[1] == '/') continue;	// skip comment lines

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[SETTINGS]") {
			section = SCENE_SECTION_SETTINGS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\Textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading simon resources %s\n", simonFile);
}

void Simon::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void Simon::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int width = atoi(tokens[3].c_str());
	int height = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());
	int dx = atoi(tokens[6].c_str());
	int dy = atoi(tokens[7].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->AddByWidthHeight(ID, l, t, width, height, tex, dx, dy);
}

void Simon::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	int ani_id = atoi(tokens[0].c_str());
	int isLoop = atoi(tokens[1].c_str());

	LPANIMATION ani = new CAnimation(100, isLoop);

	for (int i = 2; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void Simon::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void Simon::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	int id = atoi(tokens[0].c_str());
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(id);

	if (tokens[1] == "SIMON")
	{
		SetAnimationSet(ani_set);
	}
	else if (tokens[1] == "MORNINGSTAR")
	{
		
		SetAnimationSetMorningStar(ani_set);
	}
	else
		DebugOut(L"[ERROR] Unknown scene setting %s\n", ToWSTR(tokens[0]).c_str());
}

