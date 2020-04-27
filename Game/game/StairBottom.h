#pragma once
#include "GameObject.h"
class StairBottom : public CGameObject
{
public:
	StairBottom(int _nx);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	~StairBottom();
};

