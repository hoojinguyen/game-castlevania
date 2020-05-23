#pragma once
#include "GameObject.h"

class Gate : public CGameObject
{
public:
	Gate();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	~Gate();
};

