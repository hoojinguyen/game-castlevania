#pragma once
#include "GameObject.h"
#include "BrokenBrickEffect.h"

class BrickHidden : public CGameObject
{
	BrokenBrickEffect* listEffect[4];

public:
	BrickHidden();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};

