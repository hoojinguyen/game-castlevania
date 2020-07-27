#include <iostream>
#include <fstream>
#include "Utils.h"
#include "define.h"
#include "StartScene.h"

void StartScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "background")
		background = CSprites::GetInstance()->Get(atoi(tokens[1].c_str()));
	else if (tokens[0] == "bat_ani_set_id")
		batLarge->SetAnimationSet(atoi(tokens[1].c_str()));
	else if (tokens[0] == "text_ani_set_id")
		textMenu->SetAnimationSet(atoi(tokens[1].c_str()));
}

StartScene::StartScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	key_handler = new StartSceneKeyHandler(this);
}

void StartScene::SwitchScene()
{
	isSwitchScene = true;
	timeSwitchScene = GetTickCount();
	batLarge->SetPauseAni(true);
	textMenu->StartFlashingEffect();
}

void StartScene::Load()
{
	isSwitchScene = false;
	batLarge = new BatLarge();
	textMenu = new MenuText();
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
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading title screen resources %s\n", sceneFilePath);
}

void StartScene::Update(DWORD dt)
{
	textMenu->Update(dt);
	batLarge->Update(dt);
	if (isSwitchScene) {
		if (GetTickCount() - timeSwitchScene > 2000) {
			CGame::GetInstance()->SwitchScene(0);
		}
	}
}

void StartScene::Render()
{
	background->Draw(0, 0);
	textMenu->Render();
	batLarge->Render();
}

void StartScene::Unload()
{
	//SAFE_DELETE(textMenu);
	//SAFE_DELETE(batLarge);
	CScene::Unload();
}

void StartSceneKeyHandler::KeyState(BYTE* states)
{
}

void StartSceneKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	StartScene* s = dynamic_cast<StartScene*>(scence);
	s->SwitchScene();
}

void StartSceneKeyHandler::OnKeyUp(int KeyCode)
{
}