#pragma once
#include "Effect.h"

class Bat : public Effect
{
	DWORD timeStart;
	int ani;
	bool isPauseAnimation;

public:
	Bat();
	~Bat();

	void Update(DWORD dt);
	void Render();
	void SetPauseAni(bool isPause) { this->isPauseAnimation = isPause; }
	bool GetIsPauseAnimation() { return isPauseAnimation; }
	void ReStart();
};
