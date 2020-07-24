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
	LPANIMATION_SET animation_set;

public:
	Effect();
	~Effect();

	virtual void Update(DWORD dt) {}
	virtual void Render() {}
	virtual void AddAnimation(int aniId);
	
	void SetPosition(float X, float Y) { x = X, y = Y; }
	void SetEnable(bool e) { this->isEnable = e; }

	void SetAnimationSet(int ani_set_id);
	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }
};

