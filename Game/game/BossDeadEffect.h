#pragma once
#include "Effect.h"

class BossDeadEffect : public Effect
{
	int type;

public:
	~BossDeadEffect();
	BossDeadEffect(int type);
	void Update(DWORD dt);
	void Render();
	void Render(float posX, float posY);
	void SetPosition(float x, float y);
	void Enable();
};
