#pragma once
#include "GameObject.h"

class BrickMoving : public CGameObject
{
public:
	BrickMoving();

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

