#pragma once
#include "GameObject.h"
#include "CollisionEffect.h"
#include "DeadEffect.h"

class Candle : public CGameObject
{
	CollisionEffect* collisionEffect;
	DeadEffect* deadEffect;
public:
	Candle();

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	CollisionEffect* GetCollisionEffect() { return collisionEffect; }
	DeadEffect* GetDeadEffect() { return deadEffect; }
};

