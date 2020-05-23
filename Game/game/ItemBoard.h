#pragma once
#include"Effect.h"

class ItemBoard : public Effect
{
	CSprite* sprite;
	int type;
public:
	ItemBoard(int type);
	~ItemBoard();

	void SetType(int type);
	void Render();
};

