#include <iostream>
#include <fstream>

#include "Define.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "ObjectHidden.h"
#include "BoundingMap.h"
#include "Wall.h"
#include "Ground.h"

#include "Brick.h"
#include "BrickMoving.h"
#include "Torch.h"
#include "Candle.h"
#include "Gate.h"
#include "Item.h"

#include "StairBottom.h"
#include "StairTop.h"

#include "BlackKnight.h"
#include "VampireBat.h"
#include "Hunchback.h"
#include "Raven.h"
#include "Skeleton.h"
#include "Ghost.h"
#include "Zombie.h"

#include "PhantomBat.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	camera = CCamera::GetInstance();
	mapHeight = 0.0f;
	mapWidth = 0.0f;
	isGameOver = false;
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#pragma region Functions parseSection
void CPlayScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);
	float simonX, simonY;

	if (tokens.size() < 2)
		return;

	if (tokens[0] == "stage")
		stage = atoi(tokens[1].c_str());
	else if (tokens[0] == "time")
	{
		int timeDefault = atoi(tokens[1].c_str());
		if (timeDefault > 0)
		{
			defaultTimeGame = timeDefault;
		}
		remainTime = atoi(tokens[1].c_str());
	}
	else if (tokens[0] == "map_width")
		mapWidth = atoi(tokens[1].c_str());
	else if (tokens[0] == "map_height")
		mapHeight = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown scene setting %s\n", ToWSTR(tokens[0]).c_str());
}

void CPlayScene::_ParseSection_TEXTURES(string line)
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
	arrTexturesID.push_back(texID);
}

void CPlayScene::_ParseSection_SPRITES(string line)
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
	arrSpritesID.push_back(ID);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3)
		return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	int isLoop = atoi(tokens[1].c_str());

	LPANIMATION ani = new CAnimation(100, isLoop);

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 2; i < tokens.size(); i += 2) // why i+=2 ?  sprite_id | frame_time
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
	arrAnimationSetsID.push_back(ani_set_id);
}

void CPlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2)
		return;

	string pathFile = tokens[0];

	int spriteId = atoi(tokens[1].c_str());

	LPSPRITE spriteMap = CSprites::GetInstance()->Get(spriteId);

	if (tokens.size() < 1)
		return;

	tileMap = new TileMap(mapWidth, mapHeight, spriteMap, pathFile);
}

void CPlayScene::_ParseSection_GRID(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2)
		return;

	string pathFile = tokens[0];

	int cellSize = atoi(tokens[1].c_str());

	grid = new Grid(pathFile, &objects);
}

void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 4)
		return; // skip invalid lines - an object set must have at least id, x, y

	int id = atoi(tokens[0].c_str());
	int object_type = atoi(tokens[1].c_str());
	//skip name object
	float x = atof(tokens[3].c_str());
	float y = atof(tokens[4].c_str());

	//
	int width = atoi(tokens[5].c_str());
	int height = atoi(tokens[6].c_str());
	int ani_set_id = atoi(tokens[7].c_str());
	int itemType = atoi(tokens[8].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
		//Player
	case OBJECT_TYPE_SIMON:
	{
		if (simon != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before! ");
			return;
		}
		simon = Simon::GetInstance();

		int direction = atoi(tokens[9].c_str());
		float simonBackupX = atoi(tokens[10].c_str());
		float simonBackupY = atoi(tokens[11].c_str());

		simon->nx = direction;
		simon->SetPosition(x, y);
		simon->SetPositionBackup(simonBackupX, simonBackupY);

		objects.push_back(obj);
		return;
	}
	break;
	// Object Map
	case OBJECT_TYPE_TORCH:
		obj = new Torch();
		break;
	case OBJECT_TYPE_CANDLE:
		obj = new Candle();
		break;
	case OBJECT_TYPE_GATE:
		obj = new Gate();
		break;
	case OBJECT_TYPE_BRICK_MOVING:
		obj = new BrickMoving();
		break;
	case OBJECT_TYPE_BOUNGDING_MAP:
		obj = new BoundingMap();
		break;
	case OBJECT_TYPE_WALL:
		obj = new Wall();
		break;
	case OBJECT_TYPE_GROUND:
		obj = new Ground();
		break;
	case OBJECT_TYPE_BOTTOM_STAIR:
	{
		obj = new StairBottom(ani_set_id);
		obj->SetID(id);
		obj->SetPosition(x, y);
		obj->SetWidth(width);
		obj->SetHeight(height);
		obj->SetType(object_type);
		obj->SetTypeItem(-2);
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
		obj->SetTypeItem(-2);
		objects.push_back(obj);
		return;
	}
	case OBJECT_TYPE_OBJECTHIDDEN:
	{
		int scene_id = atoi(tokens[7].c_str());
		obj = new CObjectHidden(x, y, width, height, scene_id);
		obj->SetID(id);
		obj->SetTypeItem(-2);
		objects.push_back(obj);
		return;
	}
	break;

	// Object Items
	case OBJECT_TYPE_ITEM_LARGE_HEART:
		obj = new Item(ITEM_LARGE_HEART);
		break;
	case OBJECT_TYPE_ITEM_SMALL_HEART:
		obj = new Item(ITEM_SMALL_HEART);
		break;
	case OBJECT_TYPE_ITEM_MORNINGSTAR:
		obj = new Item(ITEM_MORNINGSTAR);
		break;
	case OBJECT_TYPE_ITEM_KNIFE:
		obj = new Item(ITEM_DAGGER);
		break;
	case OBJECT_TYPE_ITEM_AXE:
		obj = new Item(ITEM_AXE);
		break;
	case OBJECT_TYPE_ITEM_BOOMERANG:
		obj = new Item(ITEM_BOOMERANG);
		break;

		// Object Enemy
	case OBJECT_TYPE_VAMPIRE_BAT:
	{
		int hp = atoi(tokens[9].c_str());
		int damage = atoi(tokens[10].c_str());
		float distanceAttack = atoi(tokens[11].c_str());
		int point = atoi(tokens[12].c_str());
		obj = new VampireBat(x, y, hp, damage, distanceAttack, point);
		break;
	}
	case OBJECT_TYPE_BLACK_KNGHT:
	{
		int hp = atoi(tokens[9].c_str());
		int damage = atoi(tokens[10].c_str());
		float distanceAttack = atoi(tokens[11].c_str());
		int point = atoi(tokens[12].c_str());
		obj = new BlackKnight(x, y, hp, damage, distanceAttack, point);
		break;
	}
	case OBJECT_TYPE_GHOST:
	{
		int hp = atoi(tokens[9].c_str());
		int damage = atoi(tokens[10].c_str());
		float distanceAttack = atoi(tokens[11].c_str());
		int point = atoi(tokens[12].c_str());
		obj = new Ghost(x, y, hp, damage, distanceAttack, point);
		break;
	}
	case OBJECT_TYPE_HUNCHBACK:
	{
		int hp = atoi(tokens[9].c_str());
		int damage = atoi(tokens[10].c_str());
		float distanceAttack = atoi(tokens[11].c_str());
		int point = atoi(tokens[12].c_str());
		obj = new Hunchback(x, y, hp, damage, distanceAttack, point);
		break;
	}
	case OBJECT_TYPE_SKELETON:
	{
		int hp = atoi(tokens[9].c_str());
		int damage = atoi(tokens[10].c_str());
		float distanceAttack = atoi(tokens[11].c_str());
		int point = atoi(tokens[12].c_str());
		obj = new Skeleton(x, y, hp, damage, distanceAttack, point);
		break;
	}

	case OBJECT_TYPE_RAVEN:
	{
		int hp = atoi(tokens[9].c_str());
		int damage = atoi(tokens[10].c_str());
		float distanceAttack = atoi(tokens[11].c_str());
		int point = atoi(tokens[12].c_str());
		obj = new Raven(x, y, hp, damage, distanceAttack, point);
		break;
	}

	case OBJECT_TYPE_ZOOMBIE:
	{
		int hp = atoi(tokens[9].c_str());
		int damage = atoi(tokens[10].c_str());
		float distanceAttack = atoi(tokens[11].c_str());
		int point = atoi(tokens[12].c_str());
		int direction = atoi(tokens[13].c_str());
		obj = new Zombie(x, y, hp, damage, distanceAttack, point, direction);
		break;
	}
	case OBJECT_TYPE_PHANTOM_BAT:
		obj = new PhantomBat(x, y);
		break;


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
	obj->SetTypeItem(itemType);

	if (ani_set_id > 0)
	{
		obj->SetAnimationSet(ani_set_id);
	}

	objects.push_back(obj);
}

#pragma endregion


#pragma region Functions proccess common

bool CPlayScene::CheckOutSideBoundingMap()
{
	//float l1 = 0, t1 = 0, r1 = mapWidth, b1 = mapWidth, l2, t2, r2, b2;
	float l1 = 0, t1 = 0, r1 = mapWidth, b1 = mapHeight, l2, t2, r2, b2;
	simon->GetBoundingBox(l2, t2, r2, b2);
	//return CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2);
	return CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2) && t2 < b1;
}

void CPlayScene::_Load_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1)
		return;

	string pathFile = tokens[0];

	fstream pFile;
	pFile.open(line, fstream::in);
	string temp;

	while (pFile.good())
	{
		getline(pFile, temp);

		if (temp[0] == '/' && temp[1] == '/')
			continue; // skip comment lines
		if (temp[0] == '#')
			continue; // skip comment lines

		_ParseSection_OBJECTS(temp);
	}

	pFile.close();
}

void CPlayScene::Load()
{
	/* Set Chờ hiển thị màn đen */
	isWaitResetGame = true;
	TimeWaitedResetGame = 0;

	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

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

		if (line == "[SETTINGS]")
		{
			section = SCENE_SECTION_SETTINGS;
			continue;
		}
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
		if (line == "[OBJECTS]")
		{
			section = SCENE_SECTION_OBJECTS;
			continue;
		}
		if (line == "[TILEMAP]")
		{
			section = SCENE_SECTION_TILEMAP;
			continue;
		}
		if (line == "[GRID]")
		{
			section = SCENE_SECTION_GRID;
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
		case SCENE_SECTION_SETTINGS:
			_ParseSection_SETTINGS(line);
			break;
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
		case SCENE_SECTION_OBJECTS:
			_Load_OBJECTS(line);
			break;
		case SCENE_SECTION_TILEMAP:
			_ParseSection_TILEMAP(line);
			break;
		case SCENE_SECTION_GRID:
			_ParseSection_GRID(line);
			break;
		}
	}

	f.close();

	scoreBoard = new ScoreBoard(simon, 16);

	time = 0;

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	coObjects.clear();
	simon = NULL;

	if (tileMap)
	{
		tileMap->Unload();
		delete tileMap;
		tileMap = NULL;
	}
	if (grid)
	{
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
	if (isGameOver)
	{
		return;
	}

	if (isWaitResetGame)
	{
		TimeWaitedResetGame += dt;
		if (TimeWaitedResetGame >= TIME_LIMIT_WAIT_RESET_GAME)
		{
			isWaitResetGame = false;
		}
		else
			return;
	}

	if (simon->GetWaitingTimeToRevive() == true)
	{
		TimeWaitedResetGame += dt;
		if (TimeWaitedResetGame >= TIME_LIMIT_WAIT_RESET_GAME * 2)
		{
			TimeWaitedResetGame = 0;
			simon->SetWaitingTimeToRevive(false);
			simon->Reset();
		}
		else
			return;
	}

	if (simon->GetLife() == 0) {
		// Hien Menu game  over?
		isGameOver = true;
		return;
	}

	grid->GetListOfObjects(&coObjects, SCREEN_WIDTH, SCREEN_HEIGHT);

	for (size_t i = 0; i < listItems.size(); i++)
	{
		coObjects.push_back(listItems.at(i));
	}

	simon->Update(dt, &coObjects);

	if (simon == NULL) return;

	for (size_t i = 0; i < coObjects.size(); i++)
	{

		coObjects[i]->Update(dt, &coObjects);

		if (coObjects[i]->GetDeadth() && !dynamic_cast<Item*>(coObjects[i]))
		{
			coObjects[i]->SetDeadth(false);
			int typeItem = coObjects[i]->GetTypeItem();
			if (typeItem >= -1)
			{
				Item* item = new Item();
				if (typeItem == -1) {
					item = new Item();
				}
				else {
					item = new Item(typeItem);
				}

				item->SetEnable(true);
				item->SetPosition(coObjects[i]->x, coObjects[i]->y - 3); // Why -3
				listItems.push_back(item);
			}

			coObjects[i]->SetEnable(false);
		}
	}


	if (simon->GetKillAllEnemies())
	{
		for (int i = 0; i < coObjects.size(); i++)
		{
			if (dynamic_cast<Enemy*>(coObjects[i])) {
				Enemy* enemy = dynamic_cast<Enemy*>(coObjects[i]);
				enemy->SetHP(0);
				enemy->SetTypeItem(-2);
			}
		}
		timeKillAll += dt;
		if (timeKillAll < 400)
		{
			if ((int)(timeKillAll) % 2 == 0)
				CGame::GetInstance()->SetBackgroundColor(CROSS_COLOR_BACKGROUND);
			else
				CGame::GetInstance()->SetBackgroundColor(BACKGROUND_COLOR);
		}
		else
		{
			CGame::GetInstance()->SetBackgroundColor(BACKGROUND_COLOR);
			simon->SetKillAllEnemies(false);
			timeKillAll = 0;
		}
	}


	//update scoreBoard
	time += dt;
	remainTime = defaultTimeGame - time * 0.001;
	scoreBoard->Update(16, remainTime, stage);

	// Update camera to follow player
	D3DXVECTOR3 pos = camera->GetCameraPosition();
	float cx, cy, boundHeight;

	simon->GetPosition(cx, cy);

	boundHeight = mapHeight;

	if (mapWidth > SCREEN_WIDTH - 15) {
		if (cx < (SCREEN_WIDTH - 15) / 2) {
			cx = 0;
		}
		else if (cx + (SCREEN_WIDTH - 15) / 2 > mapWidth) {
			cx = mapWidth - (SCREEN_WIDTH - 15);
		}
		else {
			cx = cx + (SCREEN_WIDTH - 15) / 2 - (SCREEN_WIDTH - 15);
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
			cy = mapHeight - SCREEN_HEIGHT;
		}
	}
	else {
		cy = mapHeight > SCREEN_HEIGHT;
	}

	camera->SetCameraPosition((int)cx, (int)cy);

	// Không cho simon lọt khỏi map
	if (simon->x < 0)
		simon->x = 0;
	if (simon->x + SIMON_BBOX_WIDTH > mapWidth)
		simon->x = mapWidth - SIMON_BBOX_WIDTH;

	if (!CheckOutSideBoundingMap()) {
		this->Unload();
		this->Load();
		simon->Reset();
	}
}

void CPlayScene::Render()
{
	if (!isGameOver)
	{
		if (isWaitResetGame) // màn đen trước khi bắt đầu game
			return; // thoát và ko vẽ gì

		if (simon->GetWaitingTimeToRevive() == true)
			return;

		tileMap->Render(SCREEN_WIDTH, SCREEN_HEIGHT);

		grid->GetListOfObjects(&coObjects, SCREEN_WIDTH, SCREEN_HEIGHT);

		for (size_t i = 0; i < listItems.size(); i++)
		{
			listItems.at(i)->Render();
		}

		for (int i = 0; i < coObjects.size(); i++)
		{
			coObjects[i]->Render();
		}

		simon->Render();
	}
	else
	{
		// Hien Menu Game Over
		//return;
	}

	scoreBoard->Render();

}

#pragma endregion


#pragma region Functions handle keyboard

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	Simon* simon = ((CPlayScene*)scence)->GetSimon();
	CGame* game = CGame::GetInstance();

	//CGameObject* gameObject = ((CPlayScene*)scence)->GetGameObject();
	if (simon->isFreeze)
		return;

	if (KeyCode == DIK_1 || KeyCode == DIK_2 || KeyCode == DIK_3 || KeyCode == DIK_4)
	{
		simon->isOnStair = false;
		simon->isUpStair = false;
		simon->isDownStair = false;
	}

	switch (KeyCode)
	{
	case DIK_R:
	{
		simon->SetHP(SIMON_HP);
	}
	case DIK_B:
	{
		CGameObject::enableBoundingBox = !CGameObject::enableBoundingBox;
		break;
	}
	case DIK_C:
	{
		int subWeapon = simon->GetSubWeaponSwitch();
		if (subWeapon > ITEM_STOP_WATCH)
		{
			subWeapon = ITEM_DAGGER;
		}
		simon->SetTypeOfWeapon(subWeapon);
		simon->SetSubWeaponSwitch(subWeapon + 1);
		break;
	}
	case DIK_V:
	{
		int heart = simon->GetHeart();
		simon->SetHeart(heart + 5);
		break;
	}
	case DIK_0:
	{
		//simon->SetPosition(600.0f, 20.0f);
		break;
	}
	case DIK_1:
	{
		game->SwitchScene(1);
		break;
	}
	case DIK_2:
	{
		game->SwitchScene(2);
		break;
	}
	case DIK_3:
	{
		game->SwitchScene(5);
		break;
	}
	case DIK_4:
	{
		game->SwitchScene(8);
		break;
	}
	case DIK_Z:
		if (!simon->isAttacking)
		{
			simon->SetState(SIMON_STATE_ATTACKING);
		}
		break;
	case DIK_X:
		if (!simon->isJumping && !simon->isAttacking && !simon->isSitting && !simon->isOnStair)
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

	if (simon->isFreeze)
		return;

	switch (KeyCode)
	{
	case DIK_LEFT:
		simon->vx = 0;
		simon->isRunning = false;
		if (simon->isOnStair)
		{
			simon->vx = 0;
			simon->vy = 0;
		}
		break;
	case DIK_RIGHT:
		simon->vx = 0;
		simon->isRunning = false;
		if (simon->isOnStair)
		{
			simon->vx = 0;
			simon->vy = 0;
		}
		break;
	case DIK_DOWN:
		if (simon->isSitting)
		{
			simon->isSitting = false;
			simon->y -= 8;
		}
		if (simon->isOnStair)
		{
			simon->vx = 0;
			simon->vy = 0;
		}
		break;
	case DIK_UP:
		if (simon->isOnStair)
		{
			simon->vx = 0;
			simon->vy = 0;
		}
		simon->pressKeyDikUp = false;
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	Simon* simon = ((CPlayScene*)scence)->GetSimon();

	// disable control key when Simon die
	if (simon->isFreeze)
		return;
	if (simon->GetState() == SIMON_STATE_DIE)
		return;

	if (game->IsKeyDown(DIK_DOWN))
	{
		if (simon->canClimbDownStair)
		{
			simon->SetState(SIMON_STATE_CLIMB_STAIR_DOWN);
		}
		else if (simon->isOnStair)
		{
			simon->SetState(SIMON_STATE_CLIMB_STAIR_DOWN);
		}
		else
		{
			simon->SetState(SIMON_STATE_SIT_DOWN);
		}
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		if (simon->canClimbUpStair)
		{
			simon->SetState(SIMON_STATE_CLIMB_STAIR_UP);
		}
		else if (simon->isOnStair)
		{
			simon->SetState(SIMON_STATE_CLIMB_STAIR_UP);
		}
		simon->pressKeyDikUp = true;
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		if (simon->isOnStair && (!simon->canClimbDownStair || !simon->canClimbUpStair))
		{
			if (simon->directionStair == 1)
			{
				simon->SetState(SIMON_STATE_CLIMB_STAIR_UP);
			}
			else if (simon->directionStair == -1)
			{
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
		if (simon->isOnStair && (!simon->canClimbDownStair || !simon->canClimbUpStair))
		{
			if (simon->directionStair == 1)
			{
				simon->SetState(SIMON_STATE_CLIMB_STAIR_DOWN);
			}
			else if (simon->directionStair == -1)
			{
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

#pragma endregion
