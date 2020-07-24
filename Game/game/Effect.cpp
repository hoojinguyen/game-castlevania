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

void Effect::SetAnimationSet(int ani_set_id)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	SetAnimationSet(ani_set);
}