#pragma once
#include "Effect.h"

class BatLarge : public Effect
{
	DWORD timeStart;
	int ani;
	bool isPauseAnimation;

public:
	BatLarge();
	~BatLarge();

	void Update(DWORD dt);
	void Render();
	void SetPauseAni(bool isPause) { this->isPauseAnimation = isPause; }
	bool GetIsPauseAnimation() { return isPauseAnimation; }
	void ReStart();
};
