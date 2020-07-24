#pragma once
#include "Effect.h"
class MenuText : public Effect
{
	int ani;
	DWORD timeStart;
public:
	MenuText();
	~MenuText();

	void Update(DWORD dt);
	void Render();
	void StartFlashingEffect();
	void ReStart();
};
