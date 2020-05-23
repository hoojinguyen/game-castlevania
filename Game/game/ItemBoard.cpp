#include "ItemBoard.h"

ItemBoard::ItemBoard(int type)
{
	this->type = type;
}

void ItemBoard::SetType(int type)
{
	this->type = type;
}

ItemBoard::~ItemBoard()
{
}

void ItemBoard::Render()
{
	if (type != -1) {
		CSprites* sprites = CSprites::GetInstance();
		sprite = sprites->Get(type);
		sprite->DrawWithoutCamera(x, y);
	}
}
