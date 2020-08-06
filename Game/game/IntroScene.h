#pragma once
#include "Scene.h"
#include "Simon.h"
#include "ScoreBoard.h"
#include "BatSmall.h"
#include "Helicopter.h"
#include "Sound.h"

#define SCENE_INTRO_LIVE_TIME	3000

class IntroScene : public CScene
{
protected:
	Sound* sound;

	Simon* simon;
	ScoreBoard* scoreBoard;
	LPSPRITE background;

	BatSmall* bat1;
	BatSmall* bat2;
	Helicopter* helicopter;
	vector<LPGAMEOBJECT> objects;

	DWORD timeDelay;

	float bgX, bgY;

	void _ParseSection_SETTINGS(string line);

public:
	friend class IntroSceneKeyHandler;
	IntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};

class IntroSceneKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	IntroSceneKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};
