#pragma once
#include <string>
#include <vector>
#include "Simon.h"
#include "HP.h"
#include "ItemBoard.h"

class ScoreBoard
{
	ID3DXFont* font;
	RECT rect;
	Simon* simon;
	LPDIRECT3DDEVICE9 d3ddv;
	wstring information;
	CSprite* sprite;
	LPD3DXSPRITE spriteHandler;
	vector<HP*>* listSimonHP;
	vector<HP*>* listEnemyHP;
	vector<HP*>* listDyingHP;
	ItemBoard* heart;
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
	void Update(int bossHP, int time, int life, int stage);
	void Render();
};

