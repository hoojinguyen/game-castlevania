#include "BatLarge.h"

void BatLarge::Update(DWORD dt)
{
	if (GetTickCount() - timeStart > 3990) {
		ani = 1;
	}
}

void BatLarge::Render()
{
	animation_set->at(ani)->RenderWithoutCamera(184, 104, isPauseAnimation);
}

BatLarge::BatLarge()
{
	timeStart = GetTickCount();
	ani = 0;
	isPauseAnimation = false;
}

BatLarge::~BatLarge()
{
}

void BatLarge::ReStart()
{
	ani = 0;
}
