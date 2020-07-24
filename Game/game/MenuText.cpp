#include "MenuText.h"

MenuText::MenuText()
{
	ani = 0;
	timeStart = GetTickCount();
}

MenuText::~MenuText()
{
}

void MenuText::Update(DWORD dt)
{
}

void MenuText::Render()
{
	animation_set->at(ani)->RenderWithoutCamera(72, 136, false);
}

void MenuText::StartFlashingEffect()
{
	ani = 1;
}

void MenuText::ReStart()
{
	ani = 0;
}
