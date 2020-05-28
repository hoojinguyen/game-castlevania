#pragma once
#include "Effect.h"

class BossDeadEffect : public Effect
{
	int type;
public:
	void SetPosition(float x, float y);
	void Render();
	void Render(float posX, float posY);
	void Update(DWORD dt);
	void Enable();
	BossDeadEffect(int _type);
	~BossDeadEffect();
};
