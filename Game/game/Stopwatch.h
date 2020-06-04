#pragma once
#include "Weapon.h"

class Stopwatch : public Weapon
{
public:
	Stopwatch();
	~Stopwatch();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
};

