#include "BossDeadEffect.h"

BossDeadEffect::BossDeadEffect(int _type)
{
	this->type = _type;
	timeDelay = 0.0f;
	isEnable = false;
	AddAnimation(8000);
	AddAnimation(8001);
	AddAnimation(8002);
}

BossDeadEffect::~BossDeadEffect()
{
}

void BossDeadEffect::Update(DWORD dt)
{
	if (isEnable)
	{
		timeDelay += dt;
		if (timeDelay > 650)
		{
			timeDelay = 0.0f;
			isEnable = false;
		}
	}
}

void BossDeadEffect::Render()
{
	if (isEnable)
		animations[type]->Render(x, y);
}

void BossDeadEffect::Render(float posX, float posY)
{
	if (isEnable)
		animations[type]->Render(posX, posY);
}

void BossDeadEffect::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void BossDeadEffect::Enable()
{
	SetEnable(true);
}


