#pragma once
#include "GameObject.h"
class StairTop : public CGameObject
{
public:
	StairTop(int _nx);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	~StairTop();
};