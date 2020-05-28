#pragma once
#include "Weapon.h"
class Boomerang : public Weapon
{
	float startX;
public:
	int countReturn;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Boomerang(float _startX);
	~Boomerang();
};
