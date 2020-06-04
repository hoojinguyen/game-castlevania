#include "Stopwatch.h"
#include "Enemy.h"

Stopwatch::Stopwatch()
{
	useHeart = 5;
}

Stopwatch::~Stopwatch()
{
}

void Stopwatch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void Stopwatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::isStop = true;
	Enemy::StartTimeStop();
	if (Enemy::timestop_start > 5000)
		isEnable = false;
}

void Stopwatch::Render()
{
}