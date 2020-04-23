#include "ItemBoard.h"

ItemBoard::ItemBoard(int type)
{
	this->type = type;
}

ItemBoard::~ItemBoard()
{
}

void ItemBoard::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprite = sprites->Get(type);
	sprite->DrawWithoutCamera(x, y);
}
