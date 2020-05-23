#pragma once
#include <string>
#include <vector>
#include "Simon.h"
#include "HP.h"
#include "ItemBoard.h"
class ScoreBoard
{
	ID3DXFont* font;
	RECT rectLineOne;
	RECT rectLineTwo;
	RECT rectLineThree;
	Simon* simon;
	LPDIRECT3DDEVICE9 d3ddv;
	wstring lineOne;
	wstring lineTwo;
	wstring lineThree;
	CSprite* sprite;
	LPD3DXSPRITE spriteHandler;
	vector<HP*>* listSimonHP;
	vector<HP*>* listEnemyHP;
	vector<HP*>* listDyingHP;
	ItemBoard* weaponCollect;
	ItemBoard* shotCollect;
	int bossHP;
	int score;
	int time;
	int item;
	int energy;
	int life;
	int stage;
public:
	ScoreBoard(Simon* simon, int bossHP);
	~ScoreBoard();
	void Update(int bossHP, int time, int stage);
	void Render();
};

