#pragma once
#include "Weapon.h"
class FireBomb : public Weapon
{
protected:
	bool IsFiring;
	DWORD timefiring;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool IsFire() { return IsFiring; }
	FireBomb();
	~FireBomb();
};

