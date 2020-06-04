#pragma once
#include "Weapon.h"

class FireBomb : public Weapon
{
protected:
	bool isFiring;
	DWORD timefiring;

public:
	FireBomb();
	~FireBomb();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	bool GetFiring() { return isFiring; }
};

