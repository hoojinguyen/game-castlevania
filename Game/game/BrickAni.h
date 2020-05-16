#pragma once
#include "GameObject.h"

class BrickAni : public CGameObject
{
public:
	BrickAni();

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

