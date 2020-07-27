#pragma once
#include "GameObject.h"

#define BAT_INTRO_SPEED 0.025f
#define BAT_INTRO_STATE_FLY_UP 100
#define BAT_INTRO_STATE_FLY_STRAIGHT 200

class BatSmall : public CGameObject
{
public:
	BatSmall();
	~BatSmall();
	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
};

