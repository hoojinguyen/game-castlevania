#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "GSprite.h"

#include "Simon.h"
#include "Brick.h"

#include "Board.h"
#include "Item.h" 
#include "Camera.h"
#include "Map.h"
#include "Grid.h"
#include "define.h"

//#include "TileMap.h"

#define WINDOW_CLASS_NAME L"Game"
#define MAIN_WINDOW_TITLE L"Game"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

#define MAX_FRAME_RATE 60

HWND hWnd; 

Game *game;

Simon * simon;

Camera *camera;
Grid * gridGame;
Map* TileMap;

Board * board;

//TileMap* tileMapTest;

vector<LPGAMEOBJECT> ListObj; // list chua cac object
vector<Item*> ListItem; // list chứa các item

class CSampleKeyHander: public KeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode) // khi đè phím
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (KeyCode == DIK_ESCAPE)
	{
		DestroyWindow(hWnd); // thoát
	}

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
		//DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->x + 10, simon->y);
		simon->Attack(eType::MORNINGSTAR);
	}
 
}

void CSampleKeyHander::OnKeyUp(int KeyCode) // khi buông phím
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_SPACE:
		//simon->Sit();
		break; 
	}
}

void CSampleKeyHander::KeyState(BYTE *states)
{

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

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
 
void LoadResources()
{
	TextureManager* _textureManager = TextureManager::GetInstance(); // Đã gọi load resource

	TileMap = new Map();

	gridGame = new Grid();

	camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	simon = new Simon(camera, &ListItem);

	board = new Board(0, 0);

	gridGame->SetFile("Resources\\map\\file_gameobject_map1.txt"); // đọc các object từ file vào Grid
	gridGame->ReloadGrid();
	TileMap->LoadMap(eType::MAP1, "Resources/map/readfile_map_1.txt");

	//string pathFile = "resources\maps\castle_entrance\matrix.txt";
	//tileMapTest = new TileMap(768.0f, 192.0f, eType::MAP1, pathFile);

	camera->SetAllowFollowSimon(true);
	camera->SetBoundary(0.0f, (float)(TileMap->GetMapWidth() - camera->GetWidth())); // set biên camera dựa vào kích thước map
	camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight()); // backup lại biên
	camera->SetPosition(0, 0);

	simon->SetPosition(SIMON_POSITION_DEFAULT);
	simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

	ListItem.clear();
}
 
void Update(DWORD dt)
{
	//	DebugOut(L"[DT] DT: %d\n", dt);
 
	gridGame->GetListObject(ListObj, camera); // lấy hết các object trong vùng camera;

	simon->Update(dt, &ListObj);
	camera->SetPosition(simon->GetX() - Window_Width/2 + 30, camera->GetYCam() ); // cho camera chạy theo simon
	camera->Update(dt);

	for (int i = 0; i < ListObj.size(); i++)
	{
		ListObj[i]->Update(dt,&ListObj);
	}

	for (int i = 0; i < ListItem.size(); i++) // update các Item
	{
		ListItem[i]->Update(dt, &ListObj);
	}

}
 
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		TileMap->DrawMap(camera);

		//tileMapTest->Render(SCREEN_WIDTH, SCREEN_HEIGHT, camera);


		board->Render(camera);

		for (UINT i = 0; i < ListObj.size(); i++)
			ListObj[i]->Render(camera);

		for (UINT i = 0; i < ListItem.size(); i++)
			ListItem[i]->Render(camera);

		simon->Render(camera);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	hWnd = CreateGameWindow(hInstance, nCmdShow, Window_Width, Window_Height);

	game = Game::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);

	//game->Load(L"SceneManager\main.txt");

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, Window_Width, Window_Height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}