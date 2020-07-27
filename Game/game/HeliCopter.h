#pragma once
#include "GameObject.h"
#define HELICOPTER_SPEED 0.025f

class Helicopter : public CGameObject
{
public:
	Helicopter();
	~Helicopter();
	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

