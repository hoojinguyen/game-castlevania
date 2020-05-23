#pragma once
#include "Weapon.h"
class Dagger : public Weapon
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Dagger();
	~Dagger();
};

