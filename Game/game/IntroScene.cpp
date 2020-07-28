#include <iostream>
#include <fstream>

#include "IntroScene.h"
#include "Define.h"
#include "Utils.h"
#include "Define.h"
#include "Ground.h"

void IntroScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "BACKGROUND") {
		background = CSprites::GetInstance()->Get(atoi(tokens[1].c_str()));
		bgX = atof(tokens[2].c_str());
		bgY = atof(tokens[3].c_str());
	}
	else if (tokens[0] == "BATSMALL")
	{
		bat1 = new BatSmall();
		bat1->SetPosition(atof(tokens[2].c_str()), atof(tokens[3].c_str()));
		bat1->SetState(atoi(tokens[4].c_str()));

		bat2 = new BatSmall();
		bat2->SetPosition(atof(tokens[5].c_str()), atof(tokens[6].c_str()));
		bat2->SetState(atoi(tokens[7].c_str()));

		bat1->SetAnimationSet(atoi(tokens[1].c_str()));
		bat2->SetAnimationSet(atoi(tokens[1].c_str()));
	}
	else if (tokens[0] == "HELICOPTER")
	{
		helicopter = new Helicopter();
		helicopter->SetPosition(atof(tokens[2].c_str()), atof(tokens[3].c_str()));
		helicopter->SetAnimationSet(atoi(tokens[1].c_str()));
	}
	else if (tokens[0] == "GROUND")
	{
		Ground* ground = new Ground();
		ground->SetPosition(atof(tokens[1].c_str()), atof(tokens[2].c_str()));
		ground->SetWidth(atoi(tokens[3].c_str()));
		ground->SetHeight(atoi(tokens[4].c_str()));
		objects.push_back(ground);
	}
	else if (tokens[0] == "SIMON")
	{
		simon = Simon::GetInstance();
		simon->SetPosition(atof(tokens[1].c_str()), atof(tokens[2].c_str()));
	}
}

IntroScene::IntroScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	key_handler = new IntroSceneKeyHandler(this);
}

void IntroScene::Load()
{
	ifstream f;
	f.open(sceneFilePath);

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
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
		case SCENE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		}
	}

	f.close();

	scoreBoard = new ScoreBoard(simon, 16);

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void IntroScene::Update(DWORD dt)
{
	bat1->Update(dt);
	bat2->Update(dt);
	helicopter->Update(dt);
	scoreBoard->Update(16, 1000, 0);

	if (simon->x > SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH / 2)
	{
		simon->SetState(SIMON_STATE_WALK_LEFT);
	}
	simon->Update(dt, &objects);

	if (simon->x < SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH)
	{
		simon->SetPosition(simon->x, simon->y);
		simon->SetState(SIMON_STATE_INTRO);
		timeDelay += dt;
		if (timeDelay >= SCENE_INTRO_LIVE_TIME)
		{
			CGame::GetInstance()->SwitchScene(1);
		}
	}
}

void IntroScene::Render()
{
	background->DrawWithoutCamera(bgX, bgY);
	bat1->Render();
	bat2->Render();
	helicopter->Render();
	objects[0]->Render();
	simon->Render();

	scoreBoard->Render();
}

void IntroScene::Unload()
{
	//SAFE_DELETE(background);
	//SAFE_DELETE(bat1);
	//SAFE_DELETE(bat2);
	//SAFE_DELETE(helicopter);
	CScene::Unload();
}

void IntroSceneKeyHandler::KeyState(BYTE* states)
{
}

void IntroSceneKeyHandler::OnKeyDown(int KeyCode)
{
}

void IntroSceneKeyHandler::OnKeyUp(int KeyCode)
{
}
