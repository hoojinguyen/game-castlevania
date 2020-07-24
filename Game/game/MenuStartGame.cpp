#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Define.h"
#include "MenuStartGame.h"

void MenuStartGameKeyHandler::KeyState(BYTE* states)
{
}

void MenuStartGameKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	MenuStartGame* s = dynamic_cast<MenuStartGame*>(scence);
	s->SwitchScene();
}

void MenuStartGameKeyHandler::OnKeyUp(int KeyCode)
{
}

void MenuStartGame::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
	listIdTextures.push_back(texID);
}

void MenuStartGame::_ParseSection_SPRITES(string line)
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
	listIdSprites.push_back(ID);
}

void MenuStartGame::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 4) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	int ani_id = atoi(tokens[0].c_str());
	int isLoop = atoi(tokens[1].c_str());

	LPANIMATION ani = new CAnimation(100, isLoop);

	for (int i = 2; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
	listIdAnimations.push_back(ani_id);
}

void MenuStartGame::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "background")
		background = CSprites::GetInstance()->Get(atoi(tokens[1].c_str()));
	else if (tokens[0] == "bat_ani_set_id")
		batStartGame->SetAnimationSet(atoi(tokens[1].c_str()));
	else if (tokens[0] == "text_ani_set_id")
		textMenu->SetAnimationSet(atoi(tokens[1].c_str()));
}

void MenuStartGame::_ParseSection_ANIMATION_SETS(string line)
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
	listIdAnimationSets.push_back(ani_set_id);
}

MenuStartGame::MenuStartGame(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	key_handler = new MenuStartGameKeyHandler(this);
}

void MenuStartGame::SwitchScene()
{
	is_switch_scene = true;
	time_switch_scene = GetTickCount();
	batStartGame->SetPauseAni(true);
	textMenu->StartFlashingEffect();
}

void MenuStartGame::Load()
{
	is_switch_scene = false;
	batStartGame = new Bat();
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

void MenuStartGame::Update(DWORD dt)
{
	textMenu->Update(dt);
	batStartGame->Update(dt);
	if (is_switch_scene) {
		if (GetTickCount() - time_switch_scene > 2000) {
			CGame::GetInstance()->SwitchScene(1);
		}
	}
}

void MenuStartGame::Render()
{
	background->Draw(0, 0);
	textMenu->Render();
	batStartGame->Render();
}

void MenuStartGame::Unload()
{
	/*SAFE_DELETE(textTitle);
	SAFE_DELETE(batStartGame);

	CTextures::GetInstance()->Clear(listIdTextures);
	CSprites::GetInstance()->Clear(listIdSprites);
	CAnimations::GetInstance()->Clear(listIdAnimations);
	CAnimationSets::GetInstance()->Clear(listIdAnimationSets);

	listIdTextures.clear();
	listIdSprites.clear();
	listIdAnimations.clear();
	listIdAnimationSets.clear();
	SAFE_DELETE(background);*/
}
