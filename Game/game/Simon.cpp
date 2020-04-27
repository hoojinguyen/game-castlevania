#include "Simon.h"
#include "Define.h"
#include "Torch.h"
#include "Item.h"
#include "Game.h"
#include "Candle.h"
#include "Utils.h"
#include "ObjectHidden.h"
#include "BoundingMap.h"
#include "StairBottom.h"
#include "StairTop.h"

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

	timeAttackStart = 0;

	morningStar = new MorningStar();

	state = SIMON_STATE_IDLE;

}

Simon* Simon::GetInstance()
{
	if (__instance == NULL) __instance = new Simon();
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
	{
		vx = SIMON_WALKING_SPEED;
		nx = 1;
	}
	break;
	case SIMON_STATE_WALK_LEFT:
	{
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
	}
	break;
	case SIMON_STATE_JUMP:
		isJumping = true;
		isGround = false;
		vy = -SIMON_JUMP_SPEED_Y;
	case SIMON_STATE_IDLE:
		isSitting = false;
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_SIT_DOWN:
		vx = 0;
		isSitting = true;
		break;
	case SIMON_STATE_CLIMB_STAIR_UP:
		if (!isOnStair) {
			x = posXStair - 6;
		}
		if (canClimbDownStair) {
			isOnStair = false;
			isUpStair = false;
			isDownStair = false;
			y -= 2;
		}
		else {
			vx = SIMON_WALKING_SPEED / 2;
			vy = -SIMON_WALKING_SPEED / 2;
			isOnStair = true;
			isUpStair = true;
			isDownStair = false;
		}
		break;
	case SIMON_STATE_CLIMB_STAIR_DOWN:
		if (!isOnStair) {
			x = posXStair;
			y += 8;
		}
		/*if (canClimbUpStair) {
			isOnStair = false;
			isUpStair = false;
			isDownStair = false;
			y += 6;
		}
		else {
			vx = -SIMON_WALKING_SPEED / 2;
			vy = SIMON_WALKING_SPEED / 2;
			isOnStair = true;
			isUpStair = false;
			isDownStair = true;
		}*/

		vx = -SIMON_WALKING_SPEED / 2;
		vy = SIMON_WALKING_SPEED / 2;
		isOnStair = true;
		isUpStair = false;
		isDownStair = true;
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

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD now = GetTickCount();
	CGameObject::Update(dt);

	// Simple fall down
	if (!isOnStair) {
		vy += SIMON_GRAVITY * dt;
	}
	else {
		if (isUpStair) {
			nx = directionStair;
		}
		else {
			nx = directionStair;
		}
	}

	// Check xem simon có đang đánh hay ko ??
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
				if (!item->GetDead() && item->GetEnable()) {
					item->SetDead(true);
					item->SetEnable(false);
				}
			}
		}
		else if (dynamic_cast<StairTop*>(coObjects->at(i))) {
			StairTop* item = dynamic_cast<StairTop*>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			item->GetBoundingBox(l2, t2, r2, b2);

			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
			{
				canClimbDownStair = true;
				posXStair = item->x;
				posYStair = item->y;
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
				posXStair = item->x;
				posYStair = item->y;
				directionStair = item->nx;
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
			if (dynamic_cast<BoundingMap*>(e->obj))
			{
				if (!isOnStair || isDownStair) {
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
				}
				else {
					x += dx;
					if (ny < 0)
						y += dy + ny * 0.7f;
					else if (ny > 0)
						y += dy + ny * -0.7f;

				}

			}
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
					if (vx > 0)
						ani = SIMON_ANI_CIMB_STAIR_UP_RIGHT;
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
					if (nx > 0) ani = SIMON_ANI_IDLE_STAIR_DOWN_LEFT;
					else ani = SIMON_ANI_IDLE_STAIR_DOWN_RIGHT;
				}
				else
				{
					if (vx > 0)
						ani = SIMON_ANI_CIMB_STAIR_DOWN_RIGHT;
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
		morningStar->SetPosition(this->x, this->y, isSitting);
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

	ResetAni(SIMON_ANI_ATTACKING_UP_STAIR_RIGHT);
	ResetAni(SIMON_ANI_ATTACKING_UP_STAIR_LEFT);


	ResetAni(SIMON_ANI_ATTACKING_DOWN_STAIR_RIGHT);
	ResetAni(SIMON_ANI_ATTACKING_DOWN_STAIR_LEFT);
}

void Simon::SetAnimationSetMorningStar(LPANIMATION_SET ani_set)
{
	morningStar->SetAnimationSet(ani_set);
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

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\Textures\\BBox\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading simon resources %s\n", simonFile);
}

void Simon::SetPosition(float x, float y)
{
	checkPointX = x;
	checkPointY = y;
	this->x = x;
	this->y = y;
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

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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

	if (tokens[0] == "animation_set")
	{
		int ani_set_id = atoi(tokens[1].c_str());
		CAnimationSets* animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		SetAnimationSet(ani_set);
	}
	else if (tokens[0] == "animation_set_whip")
	{
		int ani_set_whip_id = atoi(tokens[1].c_str());
		CAnimationSets* animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set_whip = animation_sets->Get(ani_set_whip_id);
		SetAnimationSetMorningStar(ani_set_whip);
	}
	else
		DebugOut(L"[ERROR] Unknown scene setting %s\n", ToWSTR(tokens[0]).c_str());
}

