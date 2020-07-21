#pragma once
#include "Enemy.h"
class Hunchback : public Enemy
{
	float startX, startY;
	float distanceAttack;

	DWORD timeJump;

public:
	Hunchback(float startX, float startY, int hp, int damage, float distanceAttack, int point);
	~Hunchback();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
};
