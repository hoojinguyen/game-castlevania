#pragma once
#include "GameObject.h"

class Wall : public CGameObject
{
	CSprite* sprite;
public:
	Wall();
	Wall(int width, int height);
	~Wall();

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

