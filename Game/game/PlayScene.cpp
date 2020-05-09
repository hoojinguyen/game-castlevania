﻿#include <iostream>
#include <fstream>

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "ObjectHidden.h"
#include "BoundingMap.h"
#include "Ground.h"

#include "Brick.h"
#include "Torch.h"
#include "Candle.h"
#include "Item.h"
#include "Define.h"

#include "StairBottom.h"
#include "StairTop.h"

#include "BlackKnight.h"
#include "VampireBat.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	camera = CCamera::GetInstance();
	mapHeight = 0.0f;
	mapWidth = 0.0f;
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

void CPlayScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	if (tokens[0] == "map_width")
		mapWidth = atoi(tokens[1].c_str());
	else if (tokens[0] == "map_height")
		mapHeight = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown scene setting %s\n", ToWSTR(tokens[0]).c_str());
}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
	arrTexturesID.push_back(texID);
}

void CPlayScene::_ParseSection_SPRITES(string line)
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
	arrSpritesID.push_back(ID);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	int isLoop = atoi(tokens[1].c_str());

	LPANIMATION ani = new CAnimation(100, isLoop);

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 2; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
	arrAnimationsID.push_back(ani_id);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
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
	arrAnimationSetsID.push_back(ani_set_id);

}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 4) return; // skip invalid lines - an object set must have at least id, x, y

	int id = atoi(tokens[0].c_str());
	int object_type = atoi(tokens[1].c_str());
	//skip name object
	float x = atof(tokens[3].c_str());
	float y = atof(tokens[4].c_str());

	//
	int width = atoi(tokens[5].c_str());
	int height = atoi(tokens[6].c_str());
	int ani_set_id = atoi(tokens[7].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
	{
		if (simon != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before! ");
			return;
		}
		simon = Simon::GetInstance();
		simon->SetPosition(x, y);
		objects.push_back(obj);
		return;
	}
	break;
	case OBJECT_TYPE_TORCH: obj = new Torch(); break;
	case OBJECT_TYPE_CANDLE: obj = new Candle(); break;
	case OBJECT_TYPE_ITEM_HEART: obj = new Item(ITEM_HEART); break;
	case OBJECT_TYPE_ITEM_MORNINGSTAR: obj = new Item(ITEM_MORNINGSTAR); break;
	case OBJECT_TYPE_ITEM_KNIFE: obj = new Item(ITEM_KNIFE); break;
	case OBJECT_TYPE_ITEM_AXE: obj = new Item(ITEM_AXE); break;
	case OBJECT_TYPE_ITEM_BOOMERANG: obj = new Item(ITEM_BOOMERANG); break;
	case OBJECT_TYPE_VAMPIRE_BAT: obj = new VampireBat(x, y); break;
	case OBJECT_TYPE_BLACK_KNGHT: obj = new BlackKnight(x, y); break;
	case OBJECT_TYPE_OBJECTHIDDEN:
	{
		int scene_id = atoi(tokens[7].c_str());
		obj = new CObjectHidden(x, y, width, height, scene_id);
		obj->SetID(id);
		objects.push_back(obj);
		return;
	}
	break;
	case OBJECT_TYPE_BOUNGDING_MAP: obj = new BoundingMap(); break;
		break;
	case OBJECT_TYPE_GROUND: obj = new Ground(); break;
		break;
	case OBJECT_TYPE_BOTTOM_STAIR: {
		obj = new StairBottom(ani_set_id);
		obj->SetID(id);
		obj->SetPosition(x, y);
		obj->SetWidth(width);
		obj->SetHeight(height);
		obj->SetType(object_type);
		objects.push_back(obj);
		return;
	}
	case OBJECT_TYPE_TOP_STAIR:
	{
		obj = new StairTop(ani_set_id);
		obj->SetID(id);
		obj->SetPosition(x, y);
		obj->SetWidth(width);
		obj->SetHeight(height);
		obj->SetType(object_type);
		objects.push_back(obj);
		return;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetID(id);
	obj->SetPosition(x, y);
	obj->SetWidth(width);
	obj->SetHeight(height);
	obj->SetType(object_type);

	if (ani_set_id > 0) {
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
	}

	objects.push_back(obj);
}


void CPlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	string pathFile = tokens[0];

	int spriteId = atoi(tokens[1].c_str());

	LPSPRITE spriteMap = CSprites::GetInstance()->Get(spriteId);

	if (tokens.size() < 1) return;

	tileMap = new TileMap(mapWidth, mapHeight, spriteMap, pathFile);
}

void CPlayScene::_ParseSection_GRID(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	string pathFile = tokens[0];

	int cellSize = atoi(tokens[1].c_str());

	grid = new Grid(pathFile, &objects);
}

void CPlayScene::_Load_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	string pathFile = tokens[0];

	fstream pFile;
	pFile.open(line, fstream::in);
	string temp;

	while (pFile.good())
	{
		getline(pFile, temp);

		if (temp[0] == '/' && temp[1] == '/') continue;	// skip comment lines
		if (temp[0] == '#') continue;	// skip comment lines

		_ParseSection_OBJECTS(temp);
	}

	pFile.close();
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines
		if (line[0] == '/' && line[1] == '/') continue;	// skip comment lines

		if (line == "[SETTINGS]") {
			section = SCENE_SECTION_SETTINGS; continue;
		}
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
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_TILEMAP; continue;
		}
		if (line == "[GRID]") {
			section = SCENE_SECTION_GRID; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _Load_OBJECTS(line); break;
		case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP(line); break;
		case SCENE_SECTION_GRID: _ParseSection_GRID(line); break;
		}
	}

	f.close();

	//CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\Textures\\BBox\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	scoreBoard = new ScoreBoard(simon, 16);

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	coObjects.clear();
	simon = NULL;

	if (tileMap) {
		tileMap->Unload();
		delete tileMap;
		tileMap = NULL;
	}
	if (grid) {
		grid->Unload();
		delete grid;
		grid = NULL;
	}


	CTextures::GetInstance()->Clear(arrTexturesID);
	CSprites::GetInstance()->Clear(arrSpritesID);
	CAnimations::GetInstance()->Clear(arrAnimationsID);
	CAnimationSets::GetInstance()->Clear(arrAnimationSetsID);

	arrTexturesID.clear();
	arrSpritesID.clear();
	arrAnimationsID.clear();
	arrAnimationSetsID.clear();
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way

	grid->GetListOfObjects(&coObjects, SCREEN_WIDTH, SCREEN_HEIGHT);

	simon->Update(dt, &coObjects);
	for (size_t i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Simon::Update might trigger PlayScene::Unload)
	if (simon == NULL) return;

	//update scoreBoard
	time += dt;
	scoreBoard->Update(16, 300 - time * 0.001, 3, 1);

	// Update camera to follow player
	D3DXVECTOR3 pos = camera->GetCameraPosition();
	float cx, cy, boundHeight;

	simon->GetPosition(cx, cy);

	boundHeight = mapHeight;

	if (mapWidth > SCREEN_WIDTH) {
		if (cx + simon->GetWidth() + 5 < SCREEN_WIDTH / 2) {
			cx = pos.x;
		}
		else if (cx + simon->GetWidth() + 5 + SCREEN_WIDTH / 2 > mapWidth - 1) {
			cx = mapWidth - SCREEN_WIDTH - 1;
		}
		else {
			cx = cx + simon->GetWidth() + 5 + SCREEN_WIDTH / 2 - SCREEN_WIDTH;
		}
	}
	else {
		cx = 0;
	}

	if (mapHeight > SCREEN_HEIGHT)
	{
		if (cy + simon->GetHeight() / 2 < mapHeight - SCREEN_HEIGHT / 2) {
			cy = cy + simon->GetHeight() / 2 - SCREEN_HEIGHT / 2;
		}
		else {
			cy = boundHeight - SCREEN_HEIGHT;
		}
	}
	else {
		cy = mapHeight > SCREEN_HEIGHT;
	}

	camera->SetCameraPosition((int)cx, (int)cy);

	// Không cho simon lọt khỏi map 
	if (simon->x < 0)
		simon->x = 0;
	if (simon->x + SIMON_BBOX_WIDTH + 16 > mapWidth)
		simon->x = mapWidth - SIMON_BBOX_WIDTH - 16;
	
}

void CPlayScene::Render()
{
	tileMap->Render(SCREEN_WIDTH, SCREEN_HEIGHT);

	grid->GetListOfObjects(&coObjects, SCREEN_WIDTH, SCREEN_HEIGHT);

	for (int i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Render();
	}

	simon->Render();

	scoreBoard->Render();
}


/*
	Handle Keyboard
*/
void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Simon* simon = ((CPlayScene*)scence)->GetSimon();
	if (simon->isFreeze) return;
	switch (KeyCode)
	{
	case DIK_Z:
		if (!simon->isAttacking)
		{
			simon->SetState(SIMON_STATE_ATTACKING);
		}
		break;
	case DIK_X:
		if (!simon->isJumping && !simon->isAttacking && !simon->isSitting)
		{
			simon->SetState(SIMON_STATE_JUMP);
		}
		break;
	case DIK_RIGHT:
		simon->nx = 1;
		break;
	case DIK_LEFT:
		simon->nx = -1;
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	Simon* simon = ((CPlayScene*)scence)->GetSimon();
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	if (simon->isFreeze) return;
	switch (KeyCode)
	{
	case DIK_LEFT:
		simon->vx = 0;
		simon->isRunning = false;
		if (simon->isOnStair) {
			simon->vx = 0;
			simon->vy = 0;
		}
		break;
	case DIK_RIGHT:
		simon->vx = 0;
		simon->isRunning = false;
		if (simon->isOnStair) {
			simon->vx = 0;
			simon->vy = 0;
		}
		break;
	case DIK_DOWN:
		if (simon->isSitting) {
			simon->isSitting = false;
			simon->y -= 8;
		}
		if (simon->isOnStair) {
			simon->vx = 0;
			simon->vy = 0;
		}
		break;
	case DIK_UP:
		if (simon->isOnStair) {
			simon->vx = 0;
			simon->vy = 0;
		}
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	Simon* simon = ((CPlayScene*)scence)->GetSimon();

	// disable control key when Simon die 
	if (simon->isFreeze) return;
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_DOWN))
	{
		if (simon->canClimbDownStair)
		{
			simon->SetState(SIMON_STATE_CLIMB_STAIR_DOWN);
		}
		else if (simon->isOnStair) {
			simon->SetState(SIMON_STATE_CLIMB_STAIR_DOWN);
		}
		else {
			simon->SetState(SIMON_STATE_SIT_DOWN);
		}
	}
	else if (game->IsKeyDown(DIK_UP)) {
		if (simon->canClimbUpStair)
		{
			simon->SetState(SIMON_STATE_CLIMB_STAIR_UP);
		}
		else if (simon->isOnStair) {
			simon->SetState(SIMON_STATE_CLIMB_STAIR_UP);
		}
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		if (simon->isOnStair && !simon->canClimbDownStair && !simon->canClimbUpStair) {
			if (simon->directionStair == 1)
			{
				simon->SetState(SIMON_STATE_CLIMB_STAIR_UP);
			}
			else if (simon->directionStair == -1) {
				simon->SetState(SIMON_STATE_CLIMB_STAIR_DOWN);
			}
		}
		else if (!simon->isAttacking)
		{
			simon->SetState(SIMON_STATE_WALK_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (simon->isOnStair && !simon->canClimbDownStair && !simon->canClimbUpStair) {
			if (simon->directionStair == 1)
			{
				simon->SetState(SIMON_STATE_CLIMB_STAIR_DOWN);
			}
			else if (simon->directionStair == -1) {
				simon->SetState(SIMON_STATE_CLIMB_STAIR_UP);
			}
		}
		else if (!simon->isAttacking)
		{
			simon->SetState(SIMON_STATE_WALK_LEFT);
		}
	}
	else
	{
		simon->SetState(SIMON_STATE_IDLE);
	}

	
}