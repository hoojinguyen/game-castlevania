#include "Simon.h"
#include "Define.h"
#include "Torch.h"
#include "Item.h"
#include "Game.h"
#include "Candle.h"
#include "BrickHidden.h"
#include "BrickMoving.h"
#include "Utils.h"
#include "ObjectHidden.h"
#include "BoundingMap.h"
#include "Ground.h"
#include "Wall.h"
#include "StairBottom.h"
#include "StairTop.h"
#include "Enemy.h"
#include "VampireBat.h"
#include "Zombie.h"

using namespace std;

#pragma region Functions Process Common
Simon* Simon::__instance = NULL;

Simon::Simon()
{
	hp = SIMON_HP;
	heart = SIMON_HEART;
	life = SIMON_LIFE;
	level = 0;
	score = 0;

	state = SIMON_STATE_IDLE;

	untouchable = 0;
	untouchableStart = 0;

	isAttacking = false;
	isJumping = false;
	isSitting = false;
	isRunning = false;

	isFreeze = false;

	timeFreezeStart = 0;
	timeAttackStart = 0;

	DoCaoDiDuoc = 0;
	isFirstOnStair = false;

	morningStar = new MorningStar();
	sound = Sound::GetInstance();

	isUseSubWeapons = false;
	numberSubWeaponAble = 1;

	isKillAllEnemies = false;

	isWaitingTimeToRevive = false;

	isWinnerBoss = false;

	subWeaponSwitch = ITEM_DAGGER;

	vx = 0;
	vy = 0;
}

Simon* Simon::GetInstance()
{
	if (__instance == NULL)
		__instance = new Simon();
	return __instance;
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
		if (isJumping && !isAttacking)
		{
			boxHeight -= 8;
		}

		left = x;
		top = y;

		if (isSitting)
		{
			boxHeight -= 8;
			top = y + 8;
		}
		right = left + boxWidth;
		bottom = top + boxHeight - 1;
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD now = GetTickCount();
	CGameObject::Update(dt);

	if (hp <= 0)
	{
		SetWaitingTimeToRevive(true);
		CGame::GetInstance()->SwitchScene(CGame::GetInstance()->GetNumberScene());
		//SetLife(-1);
		//SetState(SIMON_STATE_DIE);
	}

	// Simple fall down
	if (!isOnStair)
	{
		vy += SIMON_GRAVITY * dt;
	}
	else
	{
		if (isUpStair)
		{
			nx = directionStair;
		}
		else
		{
			nx = -directionStair;
		}

		DoCaoDiDuoc = DoCaoDiDuoc + abs(vy) * 18.0f; // DoCao

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
		else
		{
			DebugOut(L"DoCaoDiDuoc = %f . dy = %f . y = %f\n", DoCaoDiDuoc, dy, y);
		}
	}

	if (isAttacking)
	{
		if (!isUseSubWeapons)
		{
			morningStar->SetPosition(x, y, isSitting);
			morningStar->Update(dt, coObjects);
			if (now - timeAttackStart > (SIMON_ATTACK_TIME - 150))
			{
				morningStar->SetState(MORNINGSTAR_STATE_HIT);
			}
		}

		if (now - timeAttackStart > SIMON_ATTACK_TIME)
		{
			timeAttackStart = 0;

			isAttacking = false;
			isUseSubWeapons = false;

			morningStar->ResetAnimation();
			morningStar->SetEnable(false);

			ResetAnimationAttacking();
		}
	}

	// Update subWeapon
	HandleSimonAttackingWithSubWeapon(dt, coObjects);

	// Check trang thai simon bi dong bang
	if (isFreeze)
	{
		if (now - timeFreezeStart > TIME_FREEZE_MAX)
		{
			timeFreezeStart = 0;
			isFreeze = false;
		}
		else
		{
			vx = 0;
			vy = 0;
			isRunning = false;
		}
	}

	// Check Stairs
	if (canClimbUpStair)
	{
		canClimbUpStair = false;
	}
	if (canClimbDownStair)
	{
		canClimbDownStair = false;
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchableStart > SIMON_UNTOUCHABLE_TIME)
	{
		untouchableStart = 0;
		untouchable = 0;
	}

	if (isHurt)
	{
		if (GetTickCount() - hurtableStart > 1000)
		{
			hurtableStart = 0;
			hurtable = 0;
			isHurt = false;
			ResetAnimationHurt();
		}
	}

	if (this->GetState() != SIMON_STATE_SIT_DOWN)
		isSitting = false;

	CheckAABB(coObjects);
	CheckSweptAABB(coObjects);
}

void Simon::Render()
{
	int ani = 0;
	float posX = x, posY = y;
	if (state == SIMON_STATE_DIE)
	{
		ani = nx > 0 ? SIMON_ANI_DEATH_RIGHT : SIMON_ANI_DEATH_LEFT;
	}
	else if (state == SIMON_STATE_INTRO)
	{
		ani = SIMON_ANI_INTRO;
	}
	else
	{
		if (state == SIMON_STATE_HURT || isHurt)
		{
			if (!isOnStair) {
				ani = nx > 0 ? SIMON_ANI_HURT_RIGHT : SIMON_ANI_HURT_LEFT;
			}
		}
		if (isSitting)
		{
			if (isAttacking)
			{
				ani = nx > 0 ? SIMON_ANI_ATTACKING_SIT_RIGHT : SIMON_ANI_ATTACKING_SIT_LEFT;
			}
			else if (nx != 0)
			{
				ani = nx > 0 ? SIMON_ANI_SIT_DOWN_RIGHT : SIMON_ANI_SIT_DOWN_LEFT;
			}
			posY = y + 8;
		}
		else if (isJumping)
		{
			if (isAttacking)
			{
				ani = nx > 0 ? SIMON_ANI_ATTACKING_RIGHT : SIMON_ANI_ATTACKING_LEFT;
			}
			else if (nx != 0)
			{
				ani = nx > 0 ? SIMON_ANI_SIT_DOWN_RIGHT : SIMON_ANI_SIT_DOWN_LEFT;
			}
		}
		else if (isUpStair)
		{
			if (isAttacking)
			{
				ani = nx > 0 ? SIMON_ANI_ATTACKING_UP_STAIR_RIGHT : SIMON_ANI_ATTACKING_UP_STAIR_LEFT;
			}
			else
			{
				if (vx == 0)
				{
					ani = nx > 0 ? SIMON_ANI_IDLE_STAIR_UP_RIGHT : SIMON_ANI_IDLE_STAIR_UP_LEFT;
				}
				else
				{
					ani = vx > 0 ? SIMON_ANI_CIMB_STAIR_UP_RIGHT : SIMON_ANI_CIMB_STAIR_UP_LEFT;
				}
			}
		}
		else if (isDownStair)
		{
			if (isAttacking)
			{
				ani = nx > 0 ? SIMON_ANI_ATTACKING_DOWN_STAIR_RIGHT : SIMON_ANI_ATTACKING_DOWN_STAIR_LEFT;
			}
			else
			{
				if (vx == 0)
				{
					ani = nx > 0 ? SIMON_ANI_IDLE_STAIR_DOWN_RIGHT : SIMON_ANI_IDLE_STAIR_DOWN_LEFT;
				}
				else
				{
					ani = vx > 0 ? SIMON_ANI_CIMB_STAIR_DOWN_RIGHT : SIMON_ANI_CIMB_STAIR_DOWN_LEFT;
				}
			}
		}
		else
		{
			if (isAttacking)
			{
				ani = nx > 0 ? SIMON_ANI_ATTACKING_RIGHT : SIMON_ANI_ATTACKING_LEFT;
			}
			else
			{
				if (!isRunning)
				{
					ani = nx > 0 ? SIMON_ANI_IDLE_RIGHT : SIMON_ANI_IDLE_LEFT;
				}
				else
				{
					ani = nx > 0 ? SIMON_ANI_WALKING_RIGHT : SIMON_ANI_WALKING_LEFT;
				}
			}
		}
	}

	if (isAttacking)
	{
		bool isRight = nx > 0;
		morningStar->SetPosition(this->x, this->y, isSitting);
		morningStar->Render(isRight);
	}

	if (typeWeaponCollect >= ITEM_DAGGER && typeWeaponCollect <= ITEM_STOP_WATCH)
	{
		for (int i = 0; i < weapons.size(); i++)
		{
			if (weapons[i]->GetEnable())
				weapons[i]->Render();
		}
	}

	int alpha = 255;
	if (untouchable)
		alpha = 128;
	if (isFreeze)
	{
		animation_set->at(ani)->Render(posX, posY, isFreeze, alpha, rand() % 256, rand() % 256, rand() % 256);
	}
	else
	{
		animation_set->at(ani)->Render(posX, posY, isFreeze, alpha);
	}

	RenderBoundingBox();
}

#pragma endregion

#pragma region Functions Handle Collision
void Simon::HandleCollisionSimonWithItem(Item* item)
{
	DWORD now = GetTickCount();

	if (!item->GetDeadth() && item->GetEnable())
	{
		switch (item->GetTypeItem())
		{
		case ITEM_MORNINGSTAR:
		{
			if (morningStar->GetLevel() < MORNINGSTAR_LEVEL_3)
			{
				morningStar->SetLevel(morningStar->GetLevel() + 1);
				isFreeze = true;
				timeFreezeStart = now; // thời gian đã đóng băng
				sound->Play(SOUND_COLLECT_WEAPON);
			}
			break;
		}
		case ITEM_SMALL_HEART:
		{
			heart += 1;
			sound->Play(SOUND_COLLECT_ITEM);
			break;
		}
		case ITEM_LARGE_HEART:
		{
			heart += 5;
			sound->Play(SOUND_COLLECT_ITEM);
			break;
		}
		case ITEM_MONEY_BAG_RED:
		{
			score += 100;
			item->GetMoneyEffect()->SetEnable(true);
			sound->Play(SOUND_COLLECT_ITEM);
			break;
		}
		case ITEM_MONEY_BAG_PURPLE:
		{
			score += 400;
			item->GetMoneyEffect()->SetEnable(true);
			sound->Play(SOUND_COLLECT_ITEM);
			break;
		}
		case ITEM_MONEY_BAG_WHITE:
		{
			score += 700;
			item->GetMoneyEffect()->SetEnable(true);
			sound->Play(SOUND_COLLECT_ITEM);
			break;
		}
		case ITEM_DAGGER:
		{
			SetTypeOfWeapon(ITEM_DAGGER);
			sound->Play(SOUND_COLLECT_WEAPON);
			break;
		}
		case ITEM_AXE:
		{
			SetTypeOfWeapon(ITEM_AXE);
			sound->Play(SOUND_COLLECT_WEAPON);
			break;
		}
		case ITEM_HOLY_WATER:
		{
			SetTypeOfWeapon(ITEM_HOLY_WATER);
			sound->Play(SOUND_COLLECT_WEAPON);
			break;
		}
		case ITEM_BOOMERANG:
		{
			SetTypeOfWeapon(ITEM_BOOMERANG);
			sound->Play(SOUND_COLLECT_WEAPON);
			break;
		}
		case ITEM_STOP_WATCH:
		{
			SetTypeOfWeapon(ITEM_STOP_WATCH);
			sound->Play(SOUND_COLLECT_WEAPON);
			break;
		}
		case ITEM_BONUSES:
		{
			score += 1000;
			item->GetMoneyEffect()->SetEnable(true);
			sound->Play(SOUND_COLLECT_ITEM);
			break;
		}
		case ITEM_CROWN:
		case ITEM_CHEST:
		{
			score += 2000;
			//item->GetMoneyEffect()->SetEnable(true);
			sound->Play(SOUND_COLLECT_ITEM);
			break;
		}
		case ITEM_MAGIC_CRYSTAL:
		{
			hp = SIMON_HP;
			heart += 5;
			sound->Play(SOUND_COLLECT_ITEM);
			SetIsWinnerBoss(true);
			break;
		}
		case ITEM_DOUBLE_SHOT:
		{
			numberSubWeaponAble = 2;
			typeShotCollect = ITEM_DOUBLE_SHOT;
			sound->Play(SOUND_COLLECT_ITEM);
			break;
		}
		case ITEM_TRIPLE_SHOT:
		{
			numberSubWeaponAble = 3;
			typeShotCollect = ITEM_TRIPLE_SHOT;
			sound->Play(SOUND_COLLECT_ITEM);
			break;
		}
		case ITEM_CROSS:
		{
			SetKillAllEnemies(true);
			sound->Play(SOUND_ITEM_ALLKILL);
			break;
		}
		case ITEM_INVISIBILITY_POTION:
		{
			StartUntouchable();
			sound->Play(SOUND_ITEM_INVISIBILITYPOTION);
			break;
		}
		}
	}
	item->SetDeadth(true);
	item->SetEnable(false);
}

void Simon::HandleCollisionSimonWithEnemy(Enemy* enemy)
{
	if (enemy->vx != 0)
	{
		if (untouchable == 0)
		{
			if (enemy->isEnable)
			{
				if (hp > 0)
				{
					sound->Play(SOUND_HURT);
					hp -= enemy->GetDamage();
					StartUntouchable();
					SetState(SIMON_STATE_HURT);
					StartHurting();
					if (dynamic_cast<VampireBat*>(enemy))
					{
						enemy->SetDeadth(true);
						enemy->SetEnable(false);
						enemy->GetCollisionEffect()->SetEnable(true);
					}
				}
				else
				{
					SetState(SIMON_STATE_DIE);
					return;
					/*	SetWaitingTimeToRevive(true);
					SetLife(-1);*/
				}
			}
		}
	}
}

void Simon::CheckAABB(vector<LPGAMEOBJECT>* coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy*>(coObjects->at(i)))
		{
			Enemy* enemy = dynamic_cast<Enemy*>(coObjects->at(i));

			int scoreEnemy = enemy->GetScore(); // Set Score cho simon khi Kill enemy
			if (scoreEnemy != 0 && !enemy->isEnable)
			{
				score += scoreEnemy;
				enemy->SetScore(0);
			}

			DWORD now = GetTickCount() - enemy->respawnTime;
			if (!dynamic_cast<Zombie*>(enemy))
			{
				if (enemy->respawnTime != 0 && now > ENEMY_TIME_RESPAWN && !enemy->isEnable)
				{
					enemy->Respawn();
				}
			}

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);
			if ((CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2)))
			{

				HandleCollisionSimonWithEnemy(enemy);
			}
		}
		else if (dynamic_cast<StairBottom*>(coObjects->at(i)))
		{
			if (!isJumping)
			{
				StairBottom* stairBottom = dynamic_cast<StairBottom*>(coObjects->at(i));

				float l1, t1, r1, b1, l2, t2, r2, b2;
				GetBoundingBox(l1, t1, r1, b1);
				stairBottom->GetBoundingBox(l2, t2, r2, b2);

				if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
				{
					if (b2 > b1)
					{
						canClimbUpStair = true;
						xStair = stairBottom->x;
						yStair = stairBottom->y;
						directionStair = stairBottom->nx;
					}
				}
			}
		}
		else if (dynamic_cast<StairTop*>(coObjects->at(i)))
		{
			if (!isJumping)
			{
				StairTop* stairTop = dynamic_cast<StairTop*>(coObjects->at(i));

				float l1, t1, r1, b1, l2, t2, r2, b2;
				GetBoundingBox(l1, t1, r1, b1);
				stairTop->GetBoundingBox(l2, t2, r2, b2);

				if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2) && (t1 >= t2))
				{
					canClimbDownStair = true;
					xStair = stairTop->x + 2;
					yStair = stairTop->y;
					directionStair = stairTop->nx;
				}
			}
		}
		else if (dynamic_cast<Item*>(coObjects->at(i)))
		{
			Item* item = dynamic_cast<Item*>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			item->GetBoundingBox(l2, t2, r2, b2);

			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
			{
				HandleCollisionSimonWithItem(item);
			}
		}
	}
}

void Simon::CheckSweptAABB(vector<LPGAMEOBJECT>* coObjects)
{
	DWORD now = GetTickCount();

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

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
		if (!isFirstOnStair)
		{
			x += dx;
			y += dy;
		}
		else
		{
			isFirstOnStair = false;
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//bool isColisionGround = false;
		bool blockX = false;
		bool blockY = false;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (state != SIMON_STATE_DIE)
			{
				if ((dynamic_cast<Enemy*>(e->obj))) {
					Enemy* enemy = dynamic_cast<Enemy*>(e->obj);
					HandleCollisionSimonWithEnemy(enemy);
				}
				if (dynamic_cast<Item*>(e->obj))
				{
					Item* item = dynamic_cast<Item*>(e->obj);
					if (!item->GetDeadth() && item->GetEnable())
					{
						this->HandleCollisionSimonWithItem(item);
					}
				}
				else if (dynamic_cast<BrickHidden*>(e->obj))
				{
					BrickHidden* brick = dynamic_cast<BrickHidden*>(e->obj);
					if (brick->GetState() == BRICK_STATE_NORMAL) {
						//isColisionGround = true;
						blockX = true;
						blockY = true;
					}
				}
				else if (dynamic_cast<BrickMoving*>(e->obj))
				{
					//isColisionGround = true;
					blockY = true;
					blockX = true;
					if (e->ny < 0)
					{
						vx = e->obj->vx;
						//if (ny != 0)
						//	vy = 0;
						if (isJumping)
						{
							y -= 8;
							isJumping = false;
						}
					}
				}
				else if (dynamic_cast<Ground*>(e->obj))
				{
					if (isOnStair)
					{
						if (isDownStair)
						{
							if (e->ny < 0)
							{
								if (canClimbUpStair)
								{
									isOnStair = false;
									isUpStair = false;
									isDownStair = false;
									vx = 0;
									y -= 2;
									if (directionStair > 0)
									{
										x = xStair - 8;
									}
									else
									{
										x = xStair;
									}
								}
							}
						}
					}
					else
					{
						//isColisionGround = true;
						blockX = true;
						blockY = true;
						Ground* ground = dynamic_cast<Ground*>(e->obj);
						if (isJumping)
						{
							if (e->ny < 0)
							{
								y -= 10;
								isJumping = false;
							}
						}
						if (isHurt)
						{
							hurtableStart = 0;
							hurtable = 0;
							isHurt = false;
							vx = 0;
							ResetAnimationHurt();
						}
					}
				}
				else if (dynamic_cast<BoundingMap*>(e->obj) || dynamic_cast<Wall*>(e->obj))
				{
					//isColisionGround = true;
					blockX = true;
					blockY = true;
				}
				else if (dynamic_cast<CObjectHidden*>(e->obj))
				{
					CObjectHidden* p = dynamic_cast<CObjectHidden*>(e->obj);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
					return;
				}
			}
			else
			{
				if (dynamic_cast<Ground*>(e->obj))
				{
					//isColisionGround = true;
					blockX = true;
					blockY = true;
				}
			}
		}

		//if (isColisionGround)
		//{
		//	x += min_tx * dx + nx * 0.4f;
		//	y += min_ty * dy + ny * 0.4f;

		//	if (nx != 0) vx = 0;
		//	if (ny != 0) vy = 0;

		//}
		//else
		//{
		//	x += dx;
		//	y += dy;
		//}

		if (blockX) {
			x += min_tx * dx + nx * 0.4f;
			if (nx != 0) vx = 0;

		}
		else {
			x += dx;
		}

		if (blockY) {
			y += min_ty * dy + ny * 0.4f;
			if (ny != 0) vy = 0;

		}
		else
		{
			y += dy;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::HandleSimonAttackingWithSubWeapon(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (typeWeaponCollect >= ITEM_DAGGER && typeWeaponCollect <= ITEM_STOP_WATCH)
	{
		for (int i = 0; i < weapons.size(); i++)
		{
			if (weapons[i]->GetEnable())
				weapons[i]->Update(dt, coObjects);
		}
	}

	for (int i = 0; i < weapons.size(); i++)
	{
		if (weapons[i]->GetEnable())
		{
			if (dynamic_cast<Boomerang*>(weapons[i]))
			{
				Boomerang* weapon = dynamic_cast<Boomerang*>(weapons[i]);

				if (weapon->countReturn == 0)
				{
					continue;
				}

				float l1, t1, r1, b1, l2, t2, r2, b2;
				GetBoundingBox(l1, t1, r1, b1);
				weapons[i]->GetBoundingBox(l2, t2, r2, b2);
				if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
				{
					weapons[i]->SetEnable(false);
					heart++;
				}
			}
		}
	}
}

#pragma endregion

#pragma region Functions Reset
void Simon::Reset()
{
	level = 0;
	hp = SIMON_HP;
	heart = SIMON_HEART;
	//score = 0;
	life = life - 1;

	untouchable = 0;
	untouchableStart = 0;

	isAttacking = false;
	isJumping = false;
	isSitting = false;
	isRunning = false;
	isOnStair = false;
	isUpStair = false;
	isDownStair = false;
	isHurt = false;

	vx = 0;
	vy = 0;

	timeAttackStart = 0;

	isFreeze = false;
	timeFreezeStart = 0;

	state = SIMON_STATE_IDLE;

	DoCaoDiDuoc = 0;
	isFirstOnStair = false;

	isUseSubWeapons = false;

	numberSubWeaponAble = 1;

	isKillAllEnemies = false;

	isWinnerBoss = false;

	subWeaponSwitch = ITEM_DAGGER;

	CCamera::GetInstance()->SetIsLock(false);

	this->SetIsWinnerBoss(false);
	this->ResetBackupSimon();
	this->ResetAnimationAttacking();
	this->ResetAnimationHurt();
}

void Simon::ResetBackupSimon()
{
	this->x = xBackup;
	this->y = yBackup;
	//this->hp = SIMON_MAX_HP;
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

#pragma endregion

#pragma region Functions Get and Set
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

int Simon::GetLevelMorningStar()
{
	return morningStar->GetLevel();
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);
	DWORD currentTime = GetTickCount();

	switch (state)
	{
	case SIMON_STATE_INTRO:
	{
		vx = 0;
		break;
	}
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
		isJumping = true;
		isGround = false;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		isSitting = false;
		isRunning = false;
		//vx = 0;
		break;
	case SIMON_STATE_DIE:
		//vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_SIT_DOWN:
		vx = 0;
		isSitting = true;
		break;
	case SIMON_STATE_CLIMB_STAIR_UP:
		if (!isOnStair)
		{
			if (directionStair > 0)
			{
				x = xStair - SIMON_X_ON_STAIR_ALPHA;
			}
			else
			{
				x = xStair + SIMON_X_ON_STAIR_ALPHA;
			}
			isOnStair = true;
			isUpStair = true;
			isDownStair = false;
			isFirstOnStair = true;
		}
		else
		{
			isFirstOnStair = false;
			if (canClimbDownStair)
			{
				isOnStair = false;
				isUpStair = false;
				isDownStair = false;
				x = xStair;
				y -= SIMON_Y_ON_STAIR_JUMPING_ALPHA;
				vx = 0;
			}
			else
			{
				if (directionStair > 0)
				{
					vx = SIMON_JUMP_SPEED_STAIR;
				}
				else
				{
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
		if (!isOnStair)
		{
			if (directionStair > 0)
			{
				x = xStair;
				y += SIMON_Y_ON_STAIR_ALPHA;
			}
			else
			{
				x = xStair + SIMON_X_ON_STAIR_ALPHA;
				y = yStair + SIMON_Y_ON_STAIR_ALPHA;
			}

			isOnStair = true;
			isDownStair = true;
			isUpStair = false;
			isFirstOnStair = true;
		}
		else
		{
			if (directionStair > 0)
			{
				vx = -SIMON_JUMP_SPEED_STAIR;
			}
			else
			{
				vx = SIMON_JUMP_SPEED_STAIR;
			}
			vy = SIMON_JUMP_SPEED_STAIR;
			isOnStair = true;
			isDownStair = true;
			isUpStair = false;
			isFirstOnStair = false;
		}
		break;
	case SIMON_STATE_ATTACKING:
		if (isJumping)
		{
			y -= SIMON_Y_ATACKING_JUMPING_ALPHA;
		}
		vx = 0;
		isAttacking = true;
		timeAttackStart = currentTime;
		if (pressKeyDikUp && typeWeaponCollect >= ITEM_DAGGER && typeWeaponCollect <= ITEM_STOP_WATCH && heart > 0 && !isUseSubWeapons)
		{
			for (int i = 0; i < numberSubWeaponAble; i++)
			{
				if (heart <= 0)
				{
					break;
				}

				Weapon* weapon = nullptr;
				switch (typeWeaponCollect)
				{
				case ITEM_HOLY_WATER:
					weapon = new FireBomb();
					break;
				case ITEM_AXE:
					weapon = new Axe();
					break;
				case ITEM_DAGGER:
					weapon = new Dagger();
					break;
				case ITEM_BOOMERANG:
					weapon = new Boomerang(x);
					break;
				case ITEM_STOP_WATCH:
					weapon = new Stopwatch();
					break;
				default:
					break;
				}
				if (weapon != nullptr)
				{
					if (heart - weapon->GetUseHeart() >= 0)
					{
						isUseSubWeapons = true;
						heart -= weapon->GetUseHeart();
						weapon->SetEnable(true);
						weapon->SetPosition(this->x, this->y);
						if (this->nx == -1)
							weapon->nx = -1;
						else
							weapon->nx = 1;
						weapons.push_back(weapon);
					}
				}
			}
		}

		if (!isUseSubWeapons)
		{
			morningStar->SetEnable(true);
			morningStar->SetState(MORNINGSTAR_STATE_PREPARE);
		}
		break;
	case SIMON_STATE_HURT:
		isGround = false;
		if (isOnStair)
		{
			vx = 0;
			vy = 0;
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
			//if (dy <= 0 || vy >= 0 || dy > 0)
				vy = -0.2;
		}
		break;
	}
}

void Simon::SetTypeOfWeapon(int item)
{
	for (int i = 0; i < 3; i++)
	{
		switch (item)
		{
		case ITEM_HOLY_WATER:
			typeWeaponCollect = item;
			break;
		case ITEM_AXE:
			typeWeaponCollect = item;
			break;
		case ITEM_DAGGER:
			typeWeaponCollect = item;
			break;
		case ITEM_BOOMERANG:
			typeWeaponCollect = item;
			break;
		case ITEM_STOP_WATCH:
			typeWeaponCollect = item;
			break;
		default:
			break;
		}
	}
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

void Simon::SetPositionBackup(float xBackup, float yBackup)
{
	this->xBackup = xBackup;
	this->yBackup = yBackup;
}

#pragma endregion

#pragma region Functions Load Simon
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

		if (line[0] == '#')
			continue; // skip comment lines
		if (line[0] == '/' && line[1] == '/')
			continue; // skip comment lines

		if (line == "[TEXTURES]")
		{
			section = SCENE_SECTION_TEXTURES;
			continue;
		}
		if (line == "[SPRITES]")
		{
			section = SCENE_SECTION_SPRITES;
			continue;
		}
		if (line == "[ANIMATIONS]")
		{
			section = SCENE_SECTION_ANIMATIONS;
			continue;
		}
		if (line == "[ANIMATION_SETS]")
		{
			section = SCENE_SECTION_ANIMATION_SETS;
			continue;
		}
		if (line == "[SETTINGS]")
		{
			section = SCENE_SECTION_SETTINGS;
			continue;
		}
		if (line[0] == '[')
		{
			section = SCENE_SECTION_UNKNOWN;
			continue;
		}

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES:
			_ParseSection_TEXTURES(line);
			break;
		case SCENE_SECTION_SPRITES:
			_ParseSection_SPRITES(line);
			break;
		case SCENE_SECTION_ANIMATIONS:
			_ParseSection_ANIMATIONS(line);
			break;
		case SCENE_SECTION_ANIMATION_SETS:
			_ParseSection_ANIMATION_SETS(line);
			break;
		case SCENE_SECTION_SETTINGS:
			_ParseSection_SETTINGS(line);
			break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\Textures\\BBox-Yellow.png", D3DCOLOR_XRGB(255, 255, 0));

	DebugOut(L"[INFO] Done loading simon resources %s\n", simonFile);
}

void Simon::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5)
		return; // skip invalid lines

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

	if (tokens.size() < 6)
		return; // skip invalid lines

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

	if (tokens.size() < 3)
		return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	int ani_id = atoi(tokens[0].c_str());
	int isLoop = atoi(tokens[1].c_str());

	LPANIMATION ani = new CAnimation(100, isLoop);

	for (int i = 2; i < tokens.size(); i += 2) // why i+=2 ?  sprite_id | frame_time
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

	if (tokens.size() < 2)
		return; // skip invalid lines - an animation set must at least id and one animation id

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

	if (tokens.size() < 2)
		return;

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

#pragma endregion