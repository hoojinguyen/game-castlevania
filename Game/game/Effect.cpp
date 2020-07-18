#include "Effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}

