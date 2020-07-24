#include "Bat.h"

void Bat::Update(DWORD dt)
{
	if (GetTickCount() - timeStart > 3990) {
		ani = 1;
	}
}

void Bat::Render()
{
	animation_set->at(ani)->RenderWithoutCamera(184, 104, isPauseAnimation);
}

Bat::Bat()
{
	timeStart = GetTickCount();
	ani = 0;
	isPauseAnimation = false;
}

Bat::~Bat()
{
}

void Bat::ReStart()
{
	ani = 0;
}
