#pragma once
#include "Weapon.h"
class Dagger : public Weapon
{
public:
	Dagger();
	~Dagger();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

