#pragma once
#include "GameObject.h"

class BoundingMap : public CGameObject
{
	CSprite* sprite;

public:
	BoundingMap();
	BoundingMap(int width, int height);

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	~BoundingMap();
};

