#pragma once
#include "Scene.h"
#include "MenuText.h"
#include "Bat.h"
#include "Simon.h"

#define	SCENE_INTRO_GAME_LIVE_TIME 3000

class MenuStartGame : public CScene
{
protected:
	LPSPRITE background;
	MenuText* textMenu;
	Bat* batStartGame;

	vector<int> listIdTextures;
	vector<int> listIdSprites;
	vector<int> listIdAnimations;
	vector<int> listIdAnimationSets;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_SETTINGS(string line);
	void _ParseSection_ANIMATION_SETS(string line);

	bool is_switch_scene;
	DWORD time_switch_scene;
public:
	friend class CPlayScenceKeyHandler;
	MenuStartGame(int id, LPCWSTR filePath);
	void SwitchScene();

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};

class MenuStartGameKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	MenuStartGameKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};
