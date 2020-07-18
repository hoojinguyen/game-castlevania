#pragma once
#include "Textures.h"
#include "Sprites.h"
#include  "Animations.h"
class Effect
{
protected:
	int x, y;
	DWORD timeDelay;
	bool isEnable;
	vector<LPANIMATION> animations;

public:
	Effect();
	~Effect();

	virtual void Update(DWORD dt) {}
	virtual void Render() {}
	virtual void AddAnimation(int aniId);
	
	void SetPosition(float X, float Y) { x = X, y = Y; }
	void SetEnable(bool e) { this->isEnable = e; }
};

