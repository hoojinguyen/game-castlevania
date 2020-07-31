#pragma once
#include "GameObject.h"
class BrokenBrickEffect : public CGameObject
{
	DWORD timeStart;
	int type;
public:
	BrokenBrickEffect();
	BrokenBrickEffect(int type);
	void Render();
	void Update(DWORD dt);
	void Enable(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

