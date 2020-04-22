
#include <iostream>
#include <fstream>

#include "PlayScene.h"
#include "Utils.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	//key_handler = new CPlayScenceKeyHandler(this);
}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int row = atoi(tokens[2].c_str());
	int column = atoi(tokens[3].c_str());
	int totalFrames = atoi(tokens[4].c_str());
	int R = atoi(tokens[5].c_str());
	int G = atoi(tokens[6].c_str());
	int B = atoi(tokens[7].c_str());
	//string temp = tokens[1];

	//AddTexture(eType::MAP1, new GTexture("Resources/map/tileset_map1.png", 8, 4, 32));
	//char* pathTemp = path.c_str();
	//char* temp = "Resources/map/tileset_map1.png";
	//TextureManager::GetInstance()->AddTexture(eType::MAP1, new GTexture(temp, row, column, totalFrames));
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);
	int texID = eType(atoi(tokens[0].c_str()));
	wstring path = ToWSTR(tokens[1]);

	//char* fileTemp = "Resources/map/readfile_map_1.txt";

	//TileMap = new Map();

	//TileMap->LoadMap(eType::MAP1, fileTemp);
}

void CPlayScene::_ParseSection_GRID(string line)
{
	vector<string> tokens = split(line);
	wstring path = ToWSTR(tokens[0]);

	//gridGame = new Grid();

	//char* temp = "Resources\\map\\file_gameobject_map1.txt";

	//gridGame->SetFile(temp); // đọc các object từ file vào Grid
	//gridGame->ReloadGrid();
}

void CPlayScene::Load()
{
	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line == "[GRID]") {
			section = SCENE_SECTION_GRID; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { 
			section = SCENE_SECTION_UNKNOWN; continue; 
		}

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		case SCENE_SECTION_GRID: _ParseSection_GRID(line); break;
		//case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	//camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	//simon = new Simon(camera, &ListItem);

	//board = new Board(0, 0);

	//camera->SetAllowFollowSimon(true);
	//camera->SetBoundary(0.0f, (float)(TileMap->GetMapWidth() - camera->GetWidth())); // set biên camera dựa vào kích thước map
	//camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight()); // backup lại biên
	//camera->SetPosition(0, 0);

	//simon->SetPosition(SIMON_POSITION_DEFAULT);
	//simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

	//ListItem.clear();
}

void CPlayScene::Update(DWORD dt)
{
	gridGame->GetListObject(ListObj, camera); // lấy hết các object trong vùng camera;

	simon->Update(dt, &ListObj);
	camera->SetPosition(simon->GetX() - Window_Width / 2 + 30, camera->GetYCam()); // cho camera chạy theo simon
	camera->Update(dt);

	for (int i = 0; i < ListObj.size(); i++)
	{
		ListObj[i]->Update(dt, &ListObj);
	}

	for (int i = 0; i < ListItem.size(); i++) // update các Item
	{
		ListItem[i]->Update(dt, &ListObj);
	}
}

void CPlayScene::Render()
{
	TileMap->DrawMap(camera);

	board->Render(camera);

	for (UINT i = 0; i < ListObj.size(); i++)
		ListObj[i]->Render(camera);

	for (UINT i = 0; i < ListItem.size(); i++)
		ListItem[i]->Render(camera);

	simon->Render(camera);
}

void CPlayScene::Unload()
{
	for (int i = 0; i < ListObj.size(); i++)
		delete ListObj[i];

	ListObj.clear();
	simon = NULL;
}

/*
void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Simon* simon = ((CPlayScene*)scene)->GetSimon();

	if (KeyCode == DIK_Q)
	{
		simon->SetPosition(SIMON_POSITION_DEFAULT);
	}

	if (KeyCode == DIK_SPACE)
	{
		simon->Jump();
	}

	if (KeyCode == DIK_1)
	{
		DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->GetX() + 10, simon->GetY());
	}

	if (KeyCode == DIK_X)
	{
		simon->Attack(eType::MORNINGSTAR);
	}
}
*/
/*
void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	Game* game = Game::GetInstance();
	Simon* simon = ((CPlayScene*)scene)->GetSimon();

	if (game->IsKeyDown(DIK_DOWN))
	{
		simon->Sit();

		if (game->IsKeyDown(DIK_RIGHT))
		{
			simon->Right();
			simon->Go();
		}

		if (game->IsKeyDown(DIK_LEFT))
		{
			simon->Left();
			simon->Go();
		}

		return;
	}
	else
	{
		simon->Stop();
	}

	if (game->IsKeyDown(DIK_RIGHT))
	{
		simon->Right();
		simon->Go();
	}
	else
	{
		if (game->IsKeyDown(DIK_LEFT))
		{
			simon->Left();
			simon->Go();
		}
		else
		{
			simon->Stop();
		}
	}
}
*/

