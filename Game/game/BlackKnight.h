#pragma once
#include "Enemy.h"

class BlackKnight : public Enemy
{
	float startX, startY;
public:
	BlackKnight(float startX, float startY);
	~BlackKnight();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};

