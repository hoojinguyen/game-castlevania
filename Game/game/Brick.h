﻿#pragma once
#include "GameObject.h"

class Brick : public CGameObject
{
public:
	Brick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

