#pragma once
#include "Enemy.h"

class BlackKnight : public Enemy
{
	float startX, startY;
	float distanceGoX;

public:
	BlackKnight(float startX, float startY, int hp, int damage, float distanceGoX, int point);
	~BlackKnight();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};

