#pragma once
#include "Weapon.h"
class Stopwatch : public Weapon
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Stopwatch();
	~Stopwatch();
};

