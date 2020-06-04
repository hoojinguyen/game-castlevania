#pragma once
#include "Weapon.h"
class Boomerang : public Weapon
{
	float startX;
public:
	int countReturn;
	
	Boomerang(float _startX);
	~Boomerang();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
};
