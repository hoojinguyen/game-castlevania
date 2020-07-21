#pragma once
#include "Enemy.h"
#include "Bone.h"
#include <vector>
class Skeleton : public Enemy
{
	float startX, startY;
	float distanceAttack;
	DWORD timeAttack;
	vector<Bone *> bones;

public:
	Skeleton(float startX, float startY, int hp, int damage, float distanceAttack, int point);
	~Skeleton();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
};
