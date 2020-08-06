#include "Stopwatch.h"
#include "Enemy.h"
#include "define.h"
#include "Sound.h"

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
	if (Enemy::timestop_start > TIME_STOP_ENEMIES)
	{
		isEnable = false;
	}
}

void Stopwatch::Render()
{
}