#pragma once
#include "Enemy.h"

class VampireBat : public Enemy
{
	float startX, startY;
public:
	VampireBat(float startX, float startY);
	~VampireBat();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};

