#pragma once
#include "Effect.h"

class CollisionEffect : public Effect
{
public:
	void Render();
	void Update(DWORD dt);
	void SetPosition(float x, float y);
	CollisionEffect();
	~CollisionEffect();
};

