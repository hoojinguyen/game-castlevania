#pragma once
#include "Weapon.h"
class Axe : public Weapon
{
public:
	Axe();
	~Axe();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};
