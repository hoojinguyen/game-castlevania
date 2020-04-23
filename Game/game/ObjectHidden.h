#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CObjectHidden : public CGameObject
{
	int scene_id;	// target scene to switch to 

	int width;
	int height;
public:
	CObjectHidden(float _x, float _y, int _with, int _height, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
};