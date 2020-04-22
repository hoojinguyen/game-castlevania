#pragma once
#include "Scene.h"
#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "GSprite.h"
#include "GTexture.h"

#include "Simon.h"
#include "Brick.h"

#include "Board.h"
#include "Item.h" 
#include "Camera.h"
#include "Map.h"
#include "Grid.h"
#include "define.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_MAP 3
#define SCENE_SECTION_GRID 4
#define SCENE_SECTION_OBJECTS	5

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

class CPlayScene : public CScene
{
protected:
	Game* game;

	Simon* simon;

	Camera* camera;
	Grid* gridGame;
	Map* TileMap;

	Board* board;

	vector<LPGAMEOBJECT> ListObj; // list chua cac object
	vector<Item*> ListItem; // list chứa các item

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_GRID(string line);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	Simon* GetSimon() { return simon; }

	//friend class CPlayScenceKeyHandler;
};
/*
class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};
*/

