#pragma once
#include "Scene.h"
#include "MenuText.h"
#include "BatLarge.h"
#include "Simon.h"

#define	SCENE_INTRO_GAME_LIVE_TIME 3000

class StartScene : public CScene
{
protected:
	LPSPRITE background;
	MenuText* textMenu;
	BatLarge* batLarge;

	void _ParseSection_SETTINGS(string line);

	bool isSwitchScene;
	DWORD timeSwitchScene;
public:
	friend class CPlayScenceKeyHandler;
	StartScene(int id, LPCWSTR filePath);
	void SwitchScene();

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};

class StartSceneKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	StartSceneKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};
