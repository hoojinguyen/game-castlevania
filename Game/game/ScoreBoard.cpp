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
		simonHP->SetPosition(48 + 6 * (i + 1), 15);
		listSimonHP->push_back(simonHP);
	}

	listEnemyHP = new std::vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* enemyHP = new HP(3);
		enemyHP->SetPosition(48 + 6 * (i + 1), 25);
		listEnemyHP->push_back(enemyHP);
	}

	listDyingHP = new vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* dyingHP = new HP(2);
		dyingHP->SetPosition(48 + 6 * (i + 1), 15);
		listDyingHP->push_back(dyingHP);
	}

	font = NULL;

	D3DXFONT_DESC FontDesc = {
		12,
		7,
		5,
		5,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		FF_DONTCARE, L"font\\prstart.ttf" };


	D3DXCreateFontIndirect(d3ddv, &FontDesc, &font);

	SetRect(&rectLineOne, 53, 5, SCREEN_WIDTH, 85);
	SetRect(&rectLineTwo, 53, 15, SCREEN_WIDTH, 85);
	SetRect(&rectLineThree, 53, 25, SCREEN_WIDTH, 85);
	lineOne = L"SCORE_000000 TIME 0000 STAGE 00\n";
	lineTwo = L"PLAYER                                         -5";
	lineThree = L"ENEMY                                         P-3";

	CSprites* sprites = CSprites::GetInstance();
	sprite = sprites->Get(90000);

	weaponCollect = new ItemBoard(-1);
	shotCollect = new ItemBoard(-1);
}

ScoreBoard::~ScoreBoard()
{
}


void ScoreBoard::Update(int bossHP, int time, int stage)
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


	lineOne = scoreString + L"              " + timeString + L"             " + stageString + L"\n";
	if (simon->GetHeart() < 10)
	{
		lineTwo = L"                                    0" + to_wstring(simon->GetHeart()) + L"\n";
	}
	else {
		lineTwo = L"                                    " + to_wstring(simon->GetHeart()) + L"\n";
	}

	if (simon->GetLife() < 10)
	{
		lineThree = L"                                    0" + to_wstring(simon->GetLife()) + L"\n";
	}
	else {
		lineThree = L"                                    " + to_wstring(simon->GetLife()) + L"\n";
	}
}

void ScoreBoard::Render()
{
	sprite->DrawWithoutCamera(0, 0);

	font->DrawText(spriteHandler, lineOne.c_str(), -1, &rectLineOne, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(spriteHandler, lineTwo.c_str(), -1, &rectLineTwo, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(spriteHandler, lineThree.c_str(), -1, &rectLineThree, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

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

	switch (simon->GetTypeWeaponCollect())
	{
	case ITEM_AXE:
		weaponCollect->SetType(ITEM_BOARD_AXE);
		weaponCollect->SetPosition(156.0f, 18.0f);
		weaponCollect->Render();
		break;
	case ITEM_HOLY_WATER:
		weaponCollect->SetType(ITEM_BOARD_HOLLY_WATER);
		weaponCollect->SetPosition(157.0f, 16.0f);
		weaponCollect->Render();
		break;
	case ITEM_BOOMERANG:
		weaponCollect->SetType(ITEM_BOARD_BOOMERANG);
		weaponCollect->SetPosition(156.0f, 17.0f);
		weaponCollect->Render();
		break;
	case ITEM_DAGGER:
		weaponCollect->SetType(ITEM_BOARD_DAGGER);
		weaponCollect->SetPosition(155.0f, 19.0f);
		weaponCollect->Render();
		break;
	case ITEM_STOP_WATCH:
		weaponCollect->SetType(ITEM_BOARD_STOPWATCH);
		weaponCollect->SetPosition(156.0f, 16.0f);
		weaponCollect->Render();
		break;
	default:
		break;
	}

	switch (simon->GetTypeShotCollect())
	{
	case ITEM_DOUBLE_SHOT:
		shotCollect->SetType(ITEM_BOARD_DOUBLE_SHOT);
		shotCollect->SetPosition(217.0f, 18.0f);
		shotCollect->Render();
		break;
	case ITEM_TRIPLE_SHOT:
		shotCollect->SetType(ITEM_BOARD_TRIPLE_SHOT);
		shotCollect->SetPosition(217.0f, 18.0f);
		shotCollect->Render();
		break;
	default:
		break;
	}
}
