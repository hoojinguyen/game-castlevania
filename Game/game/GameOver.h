#pragma once
#include <string>
#include <vector>
#include "Simon.h"
class GameOver
{
	ID3DXFont* font;
	RECT rectLineTitle;
	RECT rectLineOne;
	RECT rectLineTwo;
	LPDIRECT3DDEVICE9 d3ddv;
	wstring lineTitle;
	wstring lineOne;
	wstring lineTwo;
	CSprite* sprite;
	LPD3DXSPRITE spriteHandler;


public:
	int static selected;

	GameOver();
	~GameOver();
	void Render();
};

