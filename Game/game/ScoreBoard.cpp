#include "ScoreBoard.h"
#include "Define.h"
#include "Game.h"

ScoreBoard::ScoreBoard(Simon* simon, int bossHP)
{
	this->bossHP = bossHP;
	this->simon = simon;
	this->d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	this->spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	listSimonHP = new std::vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* simonHP = new HP(1);
		simonHP->SetPosition(60 + 6 * (i + 1), 20);
		listSimonHP->push_back(simonHP);
	}

	listEnemyHP = new std::vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* enemyHP = new HP(3);
		enemyHP->SetPosition(60 + 6 * (i + 1), 30);
		listEnemyHP->push_back(enemyHP);
	}

	listDyingHP = new vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* dyingHP = new HP(2);
		dyingHP->SetPosition(60 + 6 * (i + 1), 20);
		listDyingHP->push_back(dyingHP);
	}

	heart = new ItemBoard(ITEM_BOARD_HEART);
	heart->SetPosition(191, 20);

	font = NULL;

	D3DXFONT_DESC FontDesc = {
		10,
		7,
		5,
		5,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		FF_DONTCARE, L"font\\prstart.ttf" };


	D3DXCreateFontIndirect(d3ddv, &FontDesc, &font);

	SetRect(&rect, 3, 8, SCREEN_WIDTH, 85);
	information = L"SCORE_000000 TIME 0000 STAGE 00\n";
	information += L"PLAYER                                         -5\n";
	information += L"ENEMY                                         P-3\n";
}

ScoreBoard::~ScoreBoard()
{
}


void ScoreBoard::Update(int bossHP, int time, int life, int stage)
{
	this->time = time;
	this->stage = stage;
	this->bossHP = bossHP;

	wstring scoreString = to_wstring(simon->GetScore());
	while (scoreString.length() < 6)
		scoreString = L"0" + scoreString;


	wstring timeString = to_wstring(this->time);
	while (timeString.length() < 4)
		timeString = L"0" + timeString;


	wstring stageString = to_wstring(this->stage);
	while (stageString.length() < 2)
		stageString = L"0" + stageString;


	information = L"SCORE_" + scoreString + L" TIME " + timeString + L" STAGE " + stageString + L"\n";
	information += L"PLAYER                                    -" + to_wstring(simon->GetEnergy()) + L"\n";
	information += L"ENEMY                                   P-" + to_wstring(simon->GetLife()) + L"\n";
}

void ScoreBoard::Render()
{
	RECT newRect;
	SetRect(&newRect, 0, 0, SCREEN_WIDTH, 200);
	font->DrawText(spriteHandler, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

	for (int i = 0; i < listDyingHP->size(); i++)
	{
		listDyingHP->at(i)->Render();
	}

	for (int i = 0; i < listSimonHP->size(); i++)
	{
		if (i < simon->GetHP())
		{
			listSimonHP->at(i)->Render();
		}
	}

	for (int i = 0; i < listEnemyHP->size(); i++)
	{
		if (i < bossHP)
		{
			listEnemyHP->at(i)->Render();
		}
	}

	heart->Render();
}
