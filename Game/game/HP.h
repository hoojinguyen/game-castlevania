#pragma once
#include "Effect.h"

class HP : public Effect
{
	int type;
	CSprite* sprite;
public:
	void Render();
	HP(int type);
	~HP();
};

